#include <string>
#include <process.h>
#include <windowsx.h>

#include "Network.h"
#include "Assert.h"
#include "Gomoku.h"
#include "Structs.h"

#include "OutputMemoryStream.h"
#include "InputMemoryStream.h"
#include "PlayerInfo.h"
#include "SignalManager.h"

#define SAFE_RELEASE(p) { if(p) { p->Release(); p = nullptr; } }
#define SAFE_CLEANUP(gdiplusToken) { if(gdiplusToken) { CleanUp(); }}

// coordinate이 바둑돌의 중심이 되도록 합니다.
#define TO_CENTER(coordinate)  ( coordinate - ST_FOR_CENTER_POS )  


#define WS_FIXEDSIZE    (WS_OVERLAPPED | WS_SYSMENU)		  /* 크기 변경 불가한 윈도우 스타일 */
#define BT_MENU_STYLE (WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON) /* 시작 메뉴 버튼 스타일 */


// 커스텀 윈도우 메세지 (~0x7999 까지 사용 가능)
#define MSG_DELETE_START_MENU 0x3000	 /* 시작 메뉴 삭제     */
#define MSG_DRAW_IMAGE		  0x3001	 /* 이미지 생성        */
#define MSG_DRAW_PLAYER_PLACE 0x3002	 /* 플레이어 영역 생성 */
#define MSG_DRAW_BUTTON		  0x3003	 /* 버튼 생성          */
#define MSG_DRAW_TEXT		  0x3004	 /* 텍스트 생성        */

CRITICAL_SECTION cs;
std::queue<std::pair<std::string, SOCKET>> buffers; /* 공유 자원 */


namespace gomokuGame
{
	/*----------------------------------------------------------------------------------
		Name: CreateWnd()
		Desc: 윈도우를 생성합니다.
	----------------------------------------------------------------------------------*/
	HWND CreateWnd(HINSTANCE hInstance, LPCWSTR wndClsName)
	{
		WNDCLASS wc = {};
		wc.lpfnWndProc = WndProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = wndClsName;
		wc.hbrBackground = (HBRUSH)DKGRAY_BRUSH;
		RegisterClass(&wc);

		ghInst = hInstance;

		RECT rt = { 0, 0, WND_WIDTH, WND_HEIGHT };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

		// 윈도우를 생성합니다.
		ghWnd = CreateWindowEx
		(
			0
			, wndClsName
			, wndTitleName
			, WS_FIXEDSIZE
			, WND_START_X, WND_START_Y, rt.right - rt.left, rt.bottom - rt.top // x, y, width, height
			, NULL
			, NULL
			, hInstance
			, NULL
		);
		
		return ghWnd;
	}




	/*----------------------------------------------------------------------------------
		Name: InitGlobalVariables()
		Desc: 전역변수를 초기화합니다.
	----------------------------------------------------------------------------------*/
	VOID InitGlobalVariables(HWND hWnd)
	{
		// hdc 및 임계 영역 변수를 초기화합니다.
		gHdc = GetDC(hWnd);
		InitializeCriticalSection(&cs);

		// GDI+ 및 오목판 좌표를 초기화합니다.
		if (E_FAIL == InitGameData(ghWnd))
		{
			Assert(false, "Fail to InitGameData()!");
		}

		// 이미지 파일을 초기화합니다.
		gBoardImgPtr   = Image::FromFile(IMG_GameBoard);
		gPlayer1ImgPtr = Image::FromFile(IMG_Player1);
		gPlayer2ImgPtr = Image::FromFile(IMG_Player2);

		gReadyMngForSend = std::make_shared<SignalManager>(SignalManager::eSignal::SIG_READY);
		gReadyMngForRecv = std::make_shared<SignalManager>();
	}




	/*----------------------------------------------------------------------------------
		Name: CreateRoom()
		Desc: 방을 생성합니다. (It will be a server)
	----------------------------------------------------------------------------------*/
	unsigned __stdcall CreateRoom(void* pArg)
	{
		// 시작 화면을 지웁니다.
		PostMessage(ghWnd, MSG_DELETE_START_MENU, NULL, NULL);

		// 필요 데이터 SET
		gPlayer1Ptr = std::make_shared<PlayerInfo>(PLAYER1_ID);
		gPlayer2Ptr = std::make_shared<PlayerInfo>();
		gMode = eMode::MD_BEFORE_START;
		bServer = true;

		// 게임 화면을 로드합니다.
		LoadGameScreen();
		gPhase = ePhase::PH_SERVER_1;

		// 만약 Ready 버튼이 아직 생성되지 않았다면 기다립니다.
		while (gReadyBtn == NULL);

		// Ready 버튼을 비활성화합니다.
		Assert(gReadyBtn != NULL, "gReadyBtn must not be NULL.");
		Button_Enable(gReadyBtn, false);

		/*
			↑↑↑↑↑↑↑↑↑↑↑
			상대 입장 전
			
			상대 입장 후
			↓↓↓↓↓↓↓↓↓↓↓
		*/

		// 클라이언트의 요청(입장)을 기다립니다.
		// 연결 성공 시 클라이언트와 연결된 소켓을 반환합니다.
		gSocket = WaitConnectionRequest();
		if (gSocket == INVALID_SOCKET)
		{
			Assert(false, "Failed to WaitConnectionRequest()");
		}

		// 상대 플레이어에게 내 플레이어 정보를 전송합니다.
		// 그리고 상대 플레이어의 정보를 받습니다.
		// 블로킹될 수 있음
		SendPlayerInfo(gSocket, gPlayer1Ptr);
		RecvPlayerInfo(gSocket, gPlayer2Ptr);

		// 상대 플레이어 영역을 업데이트합니다.
		ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP2_X, PP_Y, PP_WIDTH, PP_HEIGHT));
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER2_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer2ImgPtr)); // 캐릭터2
		textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P2_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer2Ptr->GetID())); // Player2 ID  
		PostMessage(ghWnd, MSG_DRAW_PLAYER_PLACE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_IMAGE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);

		gPhase = ePhase::PH_SERVER_2;
		Button_Enable(gReadyBtn, true);

		// 게임 시작 전까지 상대의 Ready 상태를 확인합니다. 
		while (gMode == eMode::MD_BEFORE_START)
		{
			//EnterCriticalSection(&cs);

			gReadyMngForRecv->RecvSignal(gSocket);
			if (gReadyMngForRecv->GetSignal() == SignalManager::eSignal::SIG_READY)
			{
				MessageBox(ghWnd, L"P2 레디 버튼 클릭", NULL, MB_OK);
				Sleep(1000);
				bReadyP2 = !bReadyP2;
				gReadyMngForRecv->SetSignal(SignalManager::eSignal::SIG_NULL);
			}

			//LeaveCriticalSection(&cs);
		}

		return 0;
	}




	/*----------------------------------------------------------------------------------
		Name: JoinRoom()
		Desc: 생성되어 있는 방이 있을 경우 입장합니다. (It will be a client)
	----------------------------------------------------------------------------------*/
	unsigned __stdcall JoinRoom(void* pArg)
	{
		// 서버에 연결합니다.
		gSocket = ConnectToServer(); 
		if (gSocket != INVALID_SOCKET)
		{
			// 시작 화면을 지웁니다.
			PostMessage(ghWnd, MSG_DELETE_START_MENU, NULL, NULL);

			// 필요 데이터 SET
			gPlayer1Ptr = std::make_shared<PlayerInfo>();
			gPlayer2Ptr = std::make_shared<PlayerInfo>(PLAYER2_ID);
			gMode       = eMode::MD_BEFORE_START;
			gPhase      = ePhase::PH_CLIENT_1;
			bServer     = false;

			// 상대의 정보를 받고, 내 정보를 전송합니다.
			RecvPlayerInfo(gSocket, gPlayer1Ptr);
			SendPlayerInfo(gSocket, gPlayer2Ptr);

			// 게임 화면을 로드합니다.
			LoadGameScreen();
			
			textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P1_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer1Ptr->GetID())); // Player1 ID  
			PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);

			// 게임 시작 전까지 상대의 Ready 상태를 확인합니다. 
			while (gMode == eMode::MD_BEFORE_START)
			{
				//EnterCriticalSection(&cs);

				gReadyMngForRecv->RecvSignal(gSocket);
				if (gReadyMngForRecv->GetSignal() == SignalManager::eSignal::SIG_READY)
				{
					MessageBox(ghWnd, L"P1 레디 버튼 클릭", NULL, MB_OK);
					Sleep(1000);
					bReadyP1 = !bReadyP1;
					gReadyMngForRecv->SetSignal(SignalManager::eSignal::SIG_NULL);
				}

				//LeaveCriticalSection(&cs);
			}
		}
		else
		{
			MessageBoxW(NULL, L"생성된 방이 없습니다.", L"Error", MB_OK);
		}

		return 0;
	}




	/*----------------------------------------------------------------------------------
		Name: EnterMsgLoop()
		Desc: 메세지 루프에 진입하는 함수입니다.
	----------------------------------------------------------------------------------*/
	static HWND hEdit[3];
	INT EnterMsgLoop()
	{
		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			// 메세지가 있다면 처리합니다.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//MessageBoxA(NULL, std::to_string(GetCurrentThreadId()).c_str(), NULL, MB_OK);
			}
			else
			{
				// 현재 스레드 메세지 큐에 메세지가 없을 경우 해당 작업을 합니다.
				// 즉 모든 윈도우 메세지를 처리 후 해당 작업을 합니다.
				// 해당 작업이 모두 끝나면 그동안 쌓여있던 메세지를 처리합니다.
				//Render();

				if ( bReadyP1 && bReadyP2 && (gMode == eMode::MD_BEFORE_START) )
				{
					MessageBox(ghWnd, L"게임 시작!", NULL, MB_OK);
					gMode = eMode::MD_ING;
				}
			}
		}

		return 0;
	}




	/*----------------------------------------------------------------------------------
		Name: WndProc()
		Desc: 운영체제에 의해 호출되는 함수로 메세지를 처리합니다.
	----------------------------------------------------------------------------------*/
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_CREATE:
				CreateStartMenu(hWnd);
				InitGlobalVariables(hWnd);
				return 0;

			case WM_DESTROY:
				SAFE_CLEANUP(gdiplusToken);
				PostQuitMessage(0);
				return 0;

			// 버튼 클릭 처리
			case WM_COMMAND:
				switch (LOWORD(wParam))
				{
					case BT_CREATE_ROOM:  // 방 생성 버튼 (It will be a host)
					{
						HANDLE tHandle = (HANDLE)_beginthreadex(NULL, 0, CreateRoom, nullptr, 0, 0); // 리스닝 스레드
						CloseHandle(tHandle);
						return 0;
					}
					
					case BT_ENTER_ROOM:   // 랜덤 방 입장 버튼 (It will be a client)  
					{
						HANDLE tHandle = (HANDLE)_beginthreadex(NULL, 0, JoinRoom, nullptr, 0, 0);
						CloseHandle(tHandle);
						return 0;
					}

					case BT_EXIT:		  // 게임 종료 버튼
					{
						if (gMode != eMode::MD_ING) // 게임 진행 중이 아닐 경우만 클릭 가능
						{
							DestroyWindow(hWnd);
						}
						return 0;
					}

					case BT_READY: // Ready 버튼
					{
						// 클릭 시 bReady 변수를 반전시키고
						// 상대에게 신호를 보냅니다.
						Assert(gSocket != NULL, "gSocket must not be NULL.");

						EnterCriticalSection(&cs);

						if (bServer)
						{
							bReadyP1 = !bReadyP1;
						}
						else
						{
							bReadyP2 = !bReadyP2;
						}
						gReadyMngForSend->SendSignal(gSocket);

						LeaveCriticalSection(&cs);
						return 0;
					}

					case BT_START: // 게임 시작 버튼
					{
						return 0;
					}
				}
				return 0;

			case WM_LBUTTONUP:
				if (gMode == eMode::MD_ING)
				{
					std::unique_ptr<MyPoint> pos;
					if (IsValidPos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), &pos))
					{
						PutStone(std::move(pos));
					}
				}
				else
				{
					auto hdc = GetDC(hWnd);
					auto xPos = GET_X_LPARAM(lParam);
					auto yPos = GET_Y_LPARAM(lParam);
					std::string str = std::to_string(xPos) + ", " + std::to_string(yPos);
					TextOutA(hdc, xPos - 50, yPos - 50, str.c_str(), str.size());
					ReleaseDC(hWnd, hdc);
				}
				return 0;

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				if (gMode >= eMode::MD_BEFORE_START)
				{
					if (bServer)
					{
						switch (gPhase)
						{
							case ePhase::PH_SERVER_1:
							{
								// 상대 영역빼고 모두 그립니다.
								DrawPlayerPlace(hdc, PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT);
								DrawMyImage(gBoardImgPtr, hdc, (float)BD_BEGIN_X, (float)BD_BEGIN_Y, (float)BD_WIDTH, (float)BD_HEIGHT);
								DrawMyImage(gPlayer1ImgPtr, hdc, (float)(PP1_X + 45), (float)(PP_Y + 45), (float)150, (float)450);
								break;
							}

							case ePhase::PH_SERVER_2:
							{
								// 상대 영역까지 모두 그립니다.
								DrawPlayerPlace(hdc, PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT);
								DrawPlayerPlace(hdc, PP2_X, PP_Y, PP_WIDTH, PP_HEIGHT);
								DrawMyImage(gBoardImgPtr, hdc, (float)BD_BEGIN_X, (float)BD_BEGIN_Y, (float)BD_WIDTH, (float)BD_HEIGHT);
								DrawMyImage(gPlayer1ImgPtr, hdc, (float)(PP1_X + 45), (float)(PP_Y + 45), (float)150, (float)450);
								DrawMyImage(gPlayer2ImgPtr, hdc, (float)(PP2_X + 45), (float)(PP_Y + 45), (float)150, (float)450);
								break;
							}
						}
					}
					else
					{
						switch (gPhase)
						{
							case ePhase::PH_CLIENT_1:
							{
								// 상대 영역까지 모두 그립니다.
								DrawPlayerPlace(hdc, PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT);
								DrawPlayerPlace(hdc, PP2_X, PP_Y, PP_WIDTH, PP_HEIGHT);
								DrawMyImage(gBoardImgPtr, hdc, (float)BD_BEGIN_X, (float)BD_BEGIN_Y, (float)BD_WIDTH, (float)BD_HEIGHT);
								DrawMyImage(gPlayer1ImgPtr, hdc, (float)(PP1_X + 45), (float)(PP_Y + 45), (float)150, (float)450);
								DrawMyImage(gPlayer2ImgPtr, hdc, (float)(PP2_X + 45), (float)(PP_Y + 45), (float)150, (float)450);
								break;
							}
						}
					}
				}
				EndPaint(hWnd, &ps);
				return 0;
			}



			/*************************** 
				   CUSTOM MESSGAE
			***************************/
			
			case MSG_DELETE_START_MENU: // 시작 메뉴를 지웁니다.
				DeleteStartMenu();
				UpdateWindow(hWnd);
				return 0;

			case MSG_DRAW_IMAGE:	    // 이미지를 그립니다.
			{
				while(!imageInfoQueue.empty())
				{
					auto imageInfo = imageInfoQueue.front();
					imageInfoQueue.pop();
					DrawMyImage(imageInfo->Image, gHdc, imageInfo->X, imageInfo->Y, imageInfo->Width, imageInfo->Height);
				}
				return 0;
			}

			case MSG_DRAW_PLAYER_PLACE: // 플레이어 영역을 그립니다.
			{
				while (!ppInfoQueue.empty())
				{
					auto ppInfo = ppInfoQueue.front(); // shared_ptr
					ppInfoQueue.pop();
					DrawPlayerPlace(gHdc, ppInfo->X, ppInfo->Y, ppInfo->Width, ppInfo->Height);
				}
				return 0;
			}

			case MSG_DRAW_BUTTON:	    // 버튼을 그립니다.
			{
				while (!btnInfoQueue.empty())
				{
					auto btnInfo = btnInfoQueue.front(); // shared_ptr
					btnInfoQueue.pop();
					DrawButton(btnInfo->X, btnInfo->Y, btnInfo->Width, btnInfo->Height, btnInfo->ButtonID, btnInfo->ButtonName);
				}
				return 0;
			}

			case MSG_DRAW_TEXT:		// 텍스트를 그립니다.
			{
				while (!textInfoQueue.empty())
				{
					auto textInfo = textInfoQueue.front(); // shared_ptr
					textInfoQueue.pop();
					DrawMyText(gHdc, textInfo->X, textInfo->Y, textInfo->Width, textInfo->Height, textInfo->Text);
				}
			}

		} // switch

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}




	/*----------------------------------------------------------------------------------
		Name: MyTimeProc()
		Desc: SetTimer 함수에 지정해 놓은 시간마다 운영체제에 의해 호출되는 콜백 함수입니다.
	----------------------------------------------------------------------------------*/
	VOID CALLBACK MyTimeProc(HWND hWnd, UINT nMsg, UINT_PTR nlDEvent, DWORD dwTime)
	{

	}




	/*----------------------------------------------------------------------------------
		Name: InitD3D()
		Desc: Direct3D를 초기화합니다.
	----------------------------------------------------------------------------------*/
	HRESULT InitD3D(HWND hWnd)
	{
		// D3D 객체를 생성합니다.
		gD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (gD3D == NULL)
		{
			return E_FAIL;
		}

		// D3D 디바이스 생성을 위한 데이터 설정
		D3DPRESENT_PARAMETERS d3dpp = {};
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		// D3D 디바이스 객체 생성
		if (FAILED( gD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &gD3D_Device )))
		{
			gD3D->Release();
			gD3D = nullptr;
			return E_FAIL;
		}

		// 스프라이트 객체 생성
		if (FAILED(D3DXCreateSprite(gD3D_Device, &gD3D_Sprite)))
		{
			gD3D_Device->Release();
			gD3D_Device = nullptr;

			gD3D->Release();
			gD3D = nullptr;

			return E_FAIL;
		}

		return S_OK;
	}




	/*----------------------------------------------------------------------------------
		Name: InitGeometry()
		Desc: 텍스쳐를 생성하고 초기화합니다.
	----------------------------------------------------------------------------------*/
	HRESULT InitGeometry()
	{
		//if (FAILED(D3DXCreateTextureFromFile(gD3D_Device, backImg, &gTexture)))
		//{
		//	MessageBox(NULL, L"The file could not find", L"Err", 0);
		//	return E_FAIL;
		//}

		auto result = D3DXCreateTextureFromFileEx
		(
			gD3D_Device
			, IMG_GameBoard
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, 0x00000001
			, 0x00000001
			, 0x00FFFFFF
			, NULL
			, NULL
			, &gTexture
		);

		D3DXCreateTextureFromFileEx
		(
			gD3D_Device
			, IMG_BlackStone
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, 0x00000001
			, 0x00000001
			, 0x00FFFFFF
			, NULL
			, NULL
			, &gTexture2
		);

		return S_OK;
	}




	/*----------------------------------------------------------------------------------
		Name: Render()
		Desc: 장면을 그립니다.(렌더링)
	----------------------------------------------------------------------------------*/
	VOID Render()
	{
		if (gD3D_Device == NULL || gD3D_Sprite == NULL)
		{
			return;
		}

		gD3D_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 160), 1.f, 0);

		// 장면은 항상 후면 버퍼에 그립니다.
		// 장면은 디바이스의 BeginScene() 함수와 EndScene() 함수 사이에서 그려야 합니다.
		// 또한 스프라이트 객체의 Draw()를 위해선 Begin()과 End() 사이에 호출해야 합니다.

		//RECT rt = { 0, 0, 1024, 768 };
		if (SUCCEEDED(gD3D_Device->BeginScene()))
		{
			gD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
			gD3D_Sprite->Draw(gTexture, NULL, NULL, NULL, D3DXCOLOR(1, 1, 1, 1));
			gD3D_Sprite->End();

			gD3D_Device->EndScene();
		}

		// 전면버퍼와 후면버퍼를 교체합니다.
		gD3D_Device->Present(NULL, NULL, NULL, NULL);
	}




	/*----------------------------------------------------------------------------------
		Name: CleanUp()
		Desc: 초기화한 객체 및 데이터를 해제합니다.
	----------------------------------------------------------------------------------*/
	VOID CleanUp()
	{
		GdiplusShutdown(gdiplusToken);
		ReleaseDC(ghWnd, gHdc);
		SAFE_RELEASE(gTexture);
		SAFE_RELEASE(gD3D_Sprite);
		SAFE_RELEASE(gD3D_Device);
		SAFE_RELEASE(gD3D);
	}




	/*----------------------------------------------------------------------------------
		Name: InitGameData()
		Desc: 게임 데이터를 초기화합니다.
	----------------------------------------------------------------------------------*/
	HRESULT InitGameData(HWND hWnd)
	{
		// GDI+ 초기화
		if (::Status::Ok != GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL))
		{
			return E_FAIL;
		}

		// 좌표 생성 및 초기화
		InitCoordinate();

		return S_OK;
	}


	
	
	/*----------------------------------------------------------------------------------
		Name: InitStartMenu()
		Desc: 시작 화면을 생성합니다.
	----------------------------------------------------------------------------------*/
	VOID CreateStartMenu(HWND hWnd)
	{
		for (size_t i = 0; i < BT_COUNT; ++i)
		{
			gStartMenuBtns[i] = CreateWindow(L"button", gButtonNames[i], BT_MENU_STYLE,
				BTN_X, BTN_Y + (BTN_DISTANCE * i), BTN_WIDTH, BTN_HEIGHT, hWnd, (HMENU)i, ghInst, NULL);
		}

		// ShowWindow() 함수는 WM_PAINT 메세지를 TRUE로 설정합니다.
		// 그러나 이에 대한 처리는 모든 메세지 큐에 담긴 메세지를
		// 모두 처리하고 나면 하기 때문에 우선순위가 낮습니다.
		// UpdateWindow() 함수를 통해 즉시 WndProc함수로 WM_PAINT 처리를 요청합니다.
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}




	/*----------------------------------------------------------------------------------
		Name: DeleteStartMenu()
		Desc: 시작 화면을 삭제합니다.
	----------------------------------------------------------------------------------*/
	VOID DeleteStartMenu()
	{
		for (size_t i = 0; i < BT_COUNT; ++i)
		{
			if (gStartMenuBtns[i])
			{
				DestroyWindow(gStartMenuBtns[i]);
				gStartMenuBtns[i] = nullptr;
			}
		}
	}




	/*----------------------------------------------------------------------------------
		Name: LoadGameScreen()
		Desc: 게임 화면을 로드합니다.
	----------------------------------------------------------------------------------*/
	VOID LoadGameScreen()
	{
		// 작업 큐에 데이터를 추가합니다.
		if (bServer)
		{
			ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT));
			btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_P1_READY_X, IGB_READY_Y, IGB_READY_WIDTH, IGB_READY_HEIGHT, (HMENU)(BT_READY), L"Ready")); // player1 준비 버튼
			textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P1_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer1Ptr->GetID())); // Player1 ID  
		}
		else
		{
			ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT));
			ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP2_X, PP_Y, PP_WIDTH, PP_HEIGHT));
			btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_P2_READY_X, IGB_READY_Y, IGB_READY_WIDTH, IGB_READY_HEIGHT, (HMENU)(BT_READY), L"Ready")); // player2 준비 버튼
			imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER2_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer2ImgPtr)); // 캐릭터2
			textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P2_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer2Ptr->GetID())); // Player2 ID  
		}

		btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_EXIT_X, IGB_EXIT_Y, IGB_EXIT_WIDTH, IGB_EXIT_HEIGHT, (HMENU)(BT_EXIT), L"Exit")); // Exit 버튼
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)BD_BEGIN_X, (float)BD_BEGIN_Y, (float)BD_WIDTH, (float)BD_HEIGHT, gBoardImgPtr)); // 오목판
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER1_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer1ImgPtr));       // 캐릭터1

		// UI 스레드가 큐에 저장된 데이터를 처리하도록 합니다.
		PostMessage(ghWnd, MSG_DRAW_PLAYER_PLACE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_BUTTON, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_IMAGE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);
	}




	/*----------------------------------------------------------------------------------
		Name: InitCoordinate()
		Desc: 오목판의 각 교차점에 대응하는 2차원 배열을 초기화합니다.
	----------------------------------------------------------------------------------*/
	VOID InitCoordinate()
	{
		coordinate_type startX = BD_BEGIN_COORDI_X;
		coordinate_type startY = BD_BEGIN_COORDI_Y;

		xPos.reserve(BD_LENGTH);
		yPos.reserve(BD_LENGTH);

		for (size_t i = 0; i < BD_LENGTH; ++i)
		{
			// 오목판 초기화
			board[i] = std::make_unique<char[]>(BD_LENGTH); 

			xPos.emplace_back(std::make_pair(startX, i));
			yPos.emplace_back(std::make_pair(startY, i));
			startX += BD_DISTANCE_DOT_TO_DOT;
			startY += BD_DISTANCE_DOT_TO_DOT;
		}
	}



	/*----------------------------------------------------------------------------------
		Name: IsValidPos()
		Desc: (x, y)가 유효한 좌표인지 확인 후 해당 좌표와 근접한 교차점의 좌표를 반환합니다.
	----------------------------------------------------------------------------------*/
	bool IsValidPos(WORD x, WORD y, std::unique_ptr<MyPoint>* pOut)
	{
		// 바둑돌은 정확히 각 교차점에만 놓여집니다.
		// 하지만 편의성을 위해 일정 거리 이내의 영역을 클릭해도
		// 유효한 클릭으로 판단하며, 클릭한 좌표와 근접한 교차점을 pOut에 저장합니다.
		for (auto i = 0; i < BD_LENGTH; ++i)
		{
			if ( (xPos[i].first - BD_VALID_CLICK_DISTANCE <= x) && (x <= xPos[i].first + BD_VALID_CLICK_DISTANCE) )
			{
				for (auto j = 0; j < BD_LENGTH; ++j)
				{
					if ( (yPos[j].first - BD_VALID_CLICK_DISTANCE <= y) && (y <= yPos[j].first + BD_VALID_CLICK_DISTANCE) )
					{
						if (bBlackTurn)
						{
							*pOut = std::make_unique<MyPoint>(xPos[i], yPos[j], true);
						}
						else
						{
							*pOut = std::make_unique<MyPoint>(xPos[i], yPos[j], false);
						}

						return true;
					}
				}
			}
		}

		// 무효한 좌표
		return false;
	}




	/*----------------------------------------------------------------------------------
		Name: PutStone()
		Desc: pos가 가리키는 위치에 바둑돌을 놓습니다.
	----------------------------------------------------------------------------------*/
	VOID PutStone(const std::unique_ptr<MyPoint> pos)
	{
		// 바둑돌 이미지를 생성합니다.
		static std::unique_ptr<Image> blackStoneImg(Image::FromFile(IMG_BlackStone));
		static std::unique_ptr<Image> whiteStoneImg(Image::FromFile(IMG_WhiteStone));
		static HDC hdc_blackStn = GetDC(ghWnd);
		static HDC hdc_whiteStn = GetDC(ghWnd);
		const char BLACK_STONE = 'b';
		const char WHITE_STONE = 'w';
		
		coordinate_type x      = TO_CENTER(pos->X.first);
		coordinate_type y      = TO_CENTER(pos->Y.first);
		idx_type        row    = pos->Y.second;
		idx_type        column = pos->X.second;

		// 이미 돌이 놓인 곳이면 무효화합니다.
		if (board[row][column] != NULL)
		{
			return;
		}
		
		// 바둑돌을 놓습니다.
		if (pos->IsBlack)
		{
			Graphics g(hdc_blackStn);
			g.DrawImage(blackStoneImg.get(), x, y, ST_LENGTH, ST_LENGTH);
			board[row][column] = BLACK_STONE;
			++gBlackStoneCount;

			// 돌이 5개 이상 놓였을 경우 검사합니다.
			if (gBlackStoneCount >= 5)
			{
				// 검은돌의 승리 조건을 확인합니다.
				if (CheckWinCondition(BLACK_STONE) == true)
				{
					MessageBoxW(NULL, L"검은돌 승", NULL, MB_OK);
				}
			}
		}
		else
		{
			Graphics g(hdc_whiteStn);
			g.DrawImage(whiteStoneImg.get(), x, y, ST_LENGTH, ST_LENGTH);
			board[row][column] = WHITE_STONE;
			++gWhiteStoneCount;

			if (gWhiteStoneCount >= 5)
			{
				if (CheckWinCondition(WHITE_STONE) == true)
				{
					MessageBoxW(NULL, L"흰돌 승", NULL, MB_OK);
				}
			}
		}

		bBlackTurn = !bBlackTurn;
	}




	/*----------------------------------------------------------------------------------
		Name: CheckWinCondition()
		Desc: stone에 대해 승리 조건을 만족하였는지 확인합니다.
	----------------------------------------------------------------------------------*/
	bool CheckWinCondition(char stone)
	{
		for (idx_type row = 0; row < BD_LENGTH; ++row)
		{
			for (idx_type col = 0; col < BD_LENGTH; ++col)
			{
				if (board[row][col] == stone)
				{
					// →↙↓↘ 방향 체크를 합니다.
					if (col + 4 <= BD_END_INDEX)
					{
						if (CheckRight(row, col, stone) == true)
						{
							return true;
						}
						if (row + 4 <= BD_END_INDEX)
						{
							if (CheckRightDown(row, col, stone) == true)
							{
								return true;
							}
						}
					}
					if (row + 4 <= BD_END_INDEX)
					{
						if (CheckDown(row, col, stone) == true)
						{
							return true;
						}
						if (col - 4 >= BD_BEGIN_INDEX)
						{
							if (CheckLeftDown(row, col, stone) == true)
							{
								return true;
							}
						}
					}
				}
			}
		}

		return false;
	}


	bool CheckRight(idx_type row, idx_type col, char stone)
	{
		size_t continuous_stone_count = 1;
		while ( (col != BD_END_INDEX) && (board[row][++col] == stone) )
		{
			++continuous_stone_count;
			if (continuous_stone_count > ST_WIN_CONDITION_COUNT)
			{
				return false;
			}
		}

		return (continuous_stone_count == ST_WIN_CONDITION_COUNT) ? true : false;
	}


	bool CheckRightDown(idx_type row, idx_type col, char stone)
	{
		size_t continuous_stone_count = 1;
		while ( (row != BD_END_INDEX && col != BD_END_INDEX) && (board[++row][++col] == stone) )
		{
			++continuous_stone_count;
			if (continuous_stone_count > ST_WIN_CONDITION_COUNT)
			{
				return false;
			}
		}

		return (continuous_stone_count == ST_WIN_CONDITION_COUNT) ? true : false;
	}
	

	bool CheckDown(idx_type row, idx_type col, char stone)
	{
		size_t continuous_stone_count = 1;
		while ( (row != BD_END_INDEX) && (board[++row][col] == stone) )
		{
			++continuous_stone_count;
			if (continuous_stone_count > ST_WIN_CONDITION_COUNT)
			{
				return false;
			}
		}

		return (continuous_stone_count == ST_WIN_CONDITION_COUNT) ? true : false;
	}


	bool CheckLeftDown(idx_type row, idx_type col, char stone)
	{
		size_t continuous_stone_count = 1;
		while ( (row != BD_END_INDEX && col != BD_BEGIN_INDEX) && (board[++row][--col] == stone) )
		{
			++continuous_stone_count;
			if (continuous_stone_count > ST_WIN_CONDITION_COUNT)
			{
				return false;
			}
		}

		return (continuous_stone_count == ST_WIN_CONDITION_COUNT) ? true : false;
	}



	// 오목판을 그려줍니다.
	VOID DrawMyImage(Gdiplus::Image* pImage, HDC hdc, float x, float y, float width, float height)
	{
		::Graphics g(hdc);
		g.DrawImage(pImage, x, y, width, height);
	}


	// 플레이어 영역을 그려줍니다.
	VOID DrawPlayerPlace(HDC hdc, int x, int y, int width, int height)
	{
		const auto realWidth  = width  + x;
		const auto realHeight = height + y;

		auto hNewBrush = ::CreateSolidBrush({ 0x00d1b499 }); // window background color(DKGRAY_BRUSH)
		auto hNewPen   = ::CreatePen(PS_INSIDEFRAME, 2, RGB(128, 128, 128));
		auto hOldBrush = ::SelectObject(hdc, hNewBrush);
		auto hOldPen   = ::SelectObject(hdc, hNewPen);

		Rectangle(hdc, x, y, realWidth, realHeight);

		::SelectObject(hdc, hOldBrush);
		::SelectObject(hdc, hOldPen);

		::DeleteObject(hNewBrush);
		::DeleteObject(hNewPen);
	}


	HWND DrawButton(int x, int y, int width, int height, HMENU buttonID, LPCWSTR buttonName)
	{
		auto btn_hWnd = CreateWindow(L"button", buttonName, BT_MENU_STYLE,
			x, y, width, height, ghWnd, buttonID, ghInst, NULL);

		auto btnID = reinterpret_cast<UINT_PTR>(buttonID);
		auto eBtnID = static_cast<eButtonID>(btnID);

		switch (eBtnID)
		{
		case BT_READY:
			gReadyBtn = btn_hWnd;
			return 0;

		case BT_START:
			gStartBtn = btn_hWnd;
			return 0;
		}

		return btn_hWnd;
	}


	inline VOID DrawMyText(HDC hdc, long x, long y, long width, long height, const char* text)
	{
		RECT rc = { x, y, x + width, y + height };
		DrawTextA(hdc, text, strlen(text), &rc, DT_CENTER);
	}



	VOID SendPlayerInfo(SOCKET sock, std::shared_ptr<PlayerInfo> info)
	{
		OutputMemoryStream ostream;
		info->Write(ostream); // info의 각 멤버를 ostream에 직렬화합니다.

		send(sock, ostream.GetBuffer(), ostream.GetSize(), 0);
	}



	// recv로 받은 직렬화된 데이터를 역직렬화하여 info로 읽어들입니다.
	const size_t gMaxPacketSize = 32;
	VOID RecvPlayerInfo(SOCKET sock, std::shared_ptr<PlayerInfo> info)
	{
		InputMemoryStream istream(gMaxPacketSize);
		Assert(istream.GetBufferPtr() != nullptr, "buffer need to memory allocation.");
		int recvBytes = recv(sock, istream.GetBufferPtr(), gMaxPacketSize, 0);
		if (recvBytes > 0)
		{
			info->Read(istream);
		}
		else
		{
			Assert(false, "recvBytes is ZERO.");
		}
	}

}
