#include <string>
#include <process.h>
#include <windowsx.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <ctime>
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

#include "Network.h"
#include "Assert.h"
#include "Gomoku.h"
#include "Structs.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "BitMacro.h"
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

#include "OutputMemoryStream.h"
#include "InputMemoryStream.h"
#include "PlayerInfo.h"
#include "SignalManager.h"

<<<<<<< HEAD
<<<<<<< HEAD
#define SAFE_CLEANUP(gdiplusToken) { if(gdiplusToken) { CleanUp(); }}
#define SET_TIMER(timeLimit)       { gTimeLimit = timeLimit; SetTimer(ghWnd, 1, 1000, MyTimeProc); }
=======
#define SAFE_RELEASE(p) { if(p) { p->Release(); p = nullptr; } }
#define SAFE_CLEANUP(gdiplusToken) { if(gdiplusToken) { CleanUp(); }}
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
#define SAFE_RELEASE(p) { if(p) { p->Release(); p = nullptr; } }
#define SAFE_CLEANUP(gdiplusToken) { if(gdiplusToken) { CleanUp(); }}
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

// coordinate�� �ٵϵ��� �߽��� �ǵ��� �մϴ�.
#define TO_CENTER(coordinate)  ( coordinate - ST_FOR_CENTER_POS )  


#define WS_FIXEDSIZE    (WS_OVERLAPPED | WS_SYSMENU)		  /* ũ�� ���� �Ұ��� ������ ��Ÿ�� */
#define BT_MENU_STYLE (WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON) /* ���� �޴� ��ư ��Ÿ�� */


// Ŀ���� ������ �޼��� (~0x7999 ���� ��� ����)
#define MSG_DELETE_START_MENU 0x3000	 /* ���� �޴� ����     */
#define MSG_DRAW_IMAGE		  0x3001	 /* �̹��� ����        */
#define MSG_DRAW_PLAYER_PLACE 0x3002	 /* �÷��̾� ���� ���� */
#define MSG_DRAW_BUTTON		  0x3003	 /* ��ư ����          */
#define MSG_DRAW_TEXT		  0x3004	 /* �ؽ�Ʈ ����        */
<<<<<<< HEAD
<<<<<<< HEAD
#define MSG_DRAW_STONE		  0x3005	 /* ����� �׸���      */

=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

CRITICAL_SECTION cs;
std::queue<std::pair<std::string, SOCKET>> buffers; /* ���� �ڿ� */


namespace gomokuGame
{
	/*----------------------------------------------------------------------------------
		Name: CreateWnd()
		Desc: �����츦 �����մϴ�.
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

		// �����츦 �����մϴ�.
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
		Desc: ���������� �ʱ�ȭ�մϴ�.
	----------------------------------------------------------------------------------*/
	VOID InitGlobalVariables(HWND hWnd)
	{
		// hdc �� �Ӱ� ���� ������ �ʱ�ȭ�մϴ�.
<<<<<<< HEAD
<<<<<<< HEAD
		gHdc        = GetDC(hWnd);
		gHdc_bStone = GetDC(hWnd);
		gHdc_wStone = GetDC(hWnd);
=======
		gHdc = GetDC(hWnd);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
		gHdc = GetDC(hWnd);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		InitializeCriticalSection(&cs);

		// GDI+ �� ������ ��ǥ�� �ʱ�ȭ�մϴ�.
		if (E_FAIL == InitGameData(ghWnd))
		{
			Assert(false, "Fail to InitGameData()!");
		}

		// �̹��� ������ �ʱ�ȭ�մϴ�.
<<<<<<< HEAD
<<<<<<< HEAD
		gBlackStoneImgPtr = Image::FromFile(IMG_BlackStone);
		gWhiteStoneImgPtr = Image::FromFile(IMG_WhiteStone);
		gBoardImgPtr      = Image::FromFile(IMG_GameBoard);
		gPlayer1ImgPtr    = Image::FromFile(IMG_Player1);
		gPlayer2ImgPtr    = Image::FromFile(IMG_Player2);


		gReadyMngForSend = std::make_shared<SignalManager>(SignalManager::eSignal::SIG_READY);
		gReadyMngForRecv = std::make_shared<SignalManager>();

		gReadyBtn = NULL;
		gStartBtn = NULL;
		gExitBtn = NULL;
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		gBoardImgPtr   = Image::FromFile(IMG_GameBoard);
		gPlayer1ImgPtr = Image::FromFile(IMG_Player1);
		gPlayer2ImgPtr = Image::FromFile(IMG_Player2);

		gReadyMngForSend = std::make_shared<SignalManager>(SignalManager::eSignal::SIG_READY);
		gReadyMngForRecv = std::make_shared<SignalManager>();
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	}




	/*----------------------------------------------------------------------------------
		Name: CreateRoom()
		Desc: ���� �����մϴ�. (It will be a server)
	----------------------------------------------------------------------------------*/
	unsigned __stdcall CreateRoom(void* pArg)
	{
		// ���� ȭ���� ����ϴ�.
		PostMessage(ghWnd, MSG_DELETE_START_MENU, NULL, NULL);

		// �ʿ� ������ SET
		gPlayer1Ptr = std::make_shared<PlayerInfo>(PLAYER1_ID);
		gPlayer2Ptr = std::make_shared<PlayerInfo>();
		gMode = eMode::MD_BEFORE_START;
		bServer = true;

		// ���� ȭ���� �ε��մϴ�.
		LoadGameScreen();
		gPhase = ePhase::PH_SERVER_1;

<<<<<<< HEAD
<<<<<<< HEAD
		// ���� Start ��ư�� ���� �������� �ʾҴٸ� ��ٸ��ϴ�.
		while (gStartBtn == NULL)
		{
			// 0.01sec
			Sleep(10);
		}

		// Start ��ư�� ��Ȱ��ȭ�մϴ�.
		Assert(gStartBtn != NULL, "gStartBtn must not be NULL.");
		Button_Enable(gStartBtn, false);
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		// ���� Ready ��ư�� ���� �������� �ʾҴٸ� ��ٸ��ϴ�.
		while (gReadyBtn == NULL);

		// Ready ��ư�� ��Ȱ��ȭ�մϴ�.
		Assert(gReadyBtn != NULL, "gReadyBtn must not be NULL.");
		Button_Enable(gReadyBtn, false);
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

		/*
			������������
			��� ���� ��
			
			��� ���� ��
			������������
		*/

		// Ŭ���̾�Ʈ�� ��û(����)�� ��ٸ��ϴ�.
		// ���� ���� �� Ŭ���̾�Ʈ�� ����� ������ ��ȯ�մϴ�.
		gSocket = WaitConnectionRequest();
		if (gSocket == INVALID_SOCKET)
		{
			Assert(false, "Failed to WaitConnectionRequest()");
		}

		// ��� �÷��̾�� �� �÷��̾� ������ �����մϴ�.
		// �׸��� ��� �÷��̾��� ������ �޽��ϴ�.
		// ���ŷ�� �� ����
		SendPlayerInfo(gSocket, gPlayer1Ptr);
		RecvPlayerInfo(gSocket, gPlayer2Ptr);

		// ��� �÷��̾� ������ ������Ʈ�մϴ�.
		ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP2_X, PP_Y, PP_WIDTH, PP_HEIGHT));
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER2_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer2ImgPtr)); // ĳ����2
		textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P2_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer2Ptr->GetID())); // Player2 ID  
		PostMessage(ghWnd, MSG_DRAW_PLAYER_PLACE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_IMAGE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);

		gPhase = ePhase::PH_SERVER_2;
<<<<<<< HEAD
<<<<<<< HEAD
=======
		Button_Enable(gReadyBtn, true);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
		Button_Enable(gReadyBtn, true);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

		// ���� ���� ������ ����� Ready ���¸� Ȯ���մϴ�. 
		while (gMode == eMode::MD_BEFORE_START)
		{
<<<<<<< HEAD
<<<<<<< HEAD
			gReadyMngForRecv->RecvSignal(gSocket);
			if (gReadyMngForRecv->GetSignal() == SignalManager::eSignal::SIG_READY)
			{
				// ����� ready ���¿� ����
				// ���� ���� ��ư�� Ȱ��ȭ/��Ȱ��ȭ �մϴ�.
				bReadyP2 = !bReadyP2;
				if (bReadyP2)
				{
					Button_Enable(gStartBtn, true);
				}
				else
				{
					Button_Enable(gStartBtn, false);
				}
				textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P2_ID_X, PI_P_ID_Y + 50, PI_P_ID_WIDTH, PI_P_ID_HEIGHT + 30, "READY"));
				PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);

				gReadyMngForRecv->SetSignal(SignalManager::eSignal::SIG_NULL);
			}
			else if (gReadyMngForRecv->GetSignal() == SignalManager::eSignal::SIG_START)
			{
				Button_Enable(gStartBtn, false);
				Button_Enable(gExitBtn, false);
				break;
			}
		}

		// ���� ������ �Ǹ� 1�ʰ� ����ϴ�.
		bErase = true;
		InvalidateRect(ghWnd, &timeRT_P2, true);
		//Sleep(500);
		gPhase = ePhase::PH_ING;
		gMode = eMode::MD_ING;
		SET_TIMER(BEGIN_TIME);
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
			//EnterCriticalSection(&cs);

			gReadyMngForRecv->RecvSignal(gSocket);
			if (gReadyMngForRecv->GetSignal() == SignalManager::eSignal::SIG_READY)
			{
				MessageBox(ghWnd, L"P2 ���� ��ư Ŭ��", NULL, MB_OK);
				Sleep(1000);
				bReadyP2 = !bReadyP2;
				gReadyMngForRecv->SetSignal(SignalManager::eSignal::SIG_NULL);
			}

			//LeaveCriticalSection(&cs);
		}
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

		return 0;
	}




	/*----------------------------------------------------------------------------------
		Name: JoinRoom()
		Desc: �����Ǿ� �ִ� ���� ���� ��� �����մϴ�. (It will be a client)
	----------------------------------------------------------------------------------*/
	unsigned __stdcall JoinRoom(void* pArg)
	{
		// ������ �����մϴ�.
		gSocket = ConnectToServer(); 
		if (gSocket != INVALID_SOCKET)
		{
			// ���� ȭ���� ����ϴ�.
			PostMessage(ghWnd, MSG_DELETE_START_MENU, NULL, NULL);

			// �ʿ� ������ SET
			gPlayer1Ptr = std::make_shared<PlayerInfo>();
			gPlayer2Ptr = std::make_shared<PlayerInfo>(PLAYER2_ID);
			gMode       = eMode::MD_BEFORE_START;
			gPhase      = ePhase::PH_CLIENT_1;
			bServer     = false;

			// ����� ������ �ް�, �� ������ �����մϴ�.
			RecvPlayerInfo(gSocket, gPlayer1Ptr);
			SendPlayerInfo(gSocket, gPlayer2Ptr);

			// ���� ȭ���� �ε��մϴ�.
			LoadGameScreen();
			
			textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P1_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer1Ptr->GetID())); // Player1 ID  
			PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);

<<<<<<< HEAD
<<<<<<< HEAD
			// ��� ���� ���� ��ȣ�� ���� ������ ��ٸ��ϴ�.
			while (gMode == eMode::MD_BEFORE_START)
			{
				gReadyMngForRecv->RecvSignal(gSocket);
				if (gReadyMngForRecv->GetSignal() == SignalManager::eSignal::SIG_START)
				{
					Button_Enable(gReadyBtn, false);
					Button_Enable(gExitBtn, false);
					gReadyMngForRecv->SetSignal(SignalManager::eSignal::SIG_NULL);

					SignalManager startMng(SignalManager::eSignal::SIG_START);
					startMng.SendSignal(gSocket);

					break;
				}
			}

			// 1�ʰ� sleep �� ���� ����
			bErase = true;
			InvalidateRect(ghWnd, &timeRT_P2, true);
			//Sleep(500);

			// ������ 60�ʾ� �ð��� �־���
			// ������ �¸� ������ ������ ������
			// ������ ���鼭 ���� ����
			gPhase = ePhase::PH_ING;
			gMode = eMode::MD_ING;
			SET_TIMER(BEGIN_TIME);
		}
		else
		{
			MessageBoxW(ghWnd, L"������ ���� �����ϴ�.", L"Error", MB_OK);
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
			// ���� ���� ������ ����� Ready ���¸� Ȯ���մϴ�. 
			while (gMode == eMode::MD_BEFORE_START)
			{
				//EnterCriticalSection(&cs);

				gReadyMngForRecv->RecvSignal(gSocket);
				if (gReadyMngForRecv->GetSignal() == SignalManager::eSignal::SIG_READY)
				{
					MessageBox(ghWnd, L"P1 ���� ��ư Ŭ��", NULL, MB_OK);
					Sleep(1000);
					bReadyP1 = !bReadyP1;
					gReadyMngForRecv->SetSignal(SignalManager::eSignal::SIG_NULL);
				}

				//LeaveCriticalSection(&cs);
			}
		}
		else
		{
			MessageBoxW(NULL, L"������ ���� �����ϴ�.", L"Error", MB_OK);
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		}

		return 0;
	}




	/*----------------------------------------------------------------------------------
		Name: EnterMsgLoop()
		Desc: �޼��� ������ �����ϴ� �Լ��Դϴ�.
	----------------------------------------------------------------------------------*/
	static HWND hEdit[3];
	INT EnterMsgLoop()
	{
		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			// �޼����� �ִٸ� ó���մϴ�.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
<<<<<<< HEAD
<<<<<<< HEAD
=======
				//MessageBoxA(NULL, std::to_string(GetCurrentThreadId()).c_str(), NULL, MB_OK);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
				//MessageBoxA(NULL, std::to_string(GetCurrentThreadId()).c_str(), NULL, MB_OK);
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
			}
			else
			{
				// ���� ������ �޼��� ť�� �޼����� ���� ��� �ش� �۾��� �մϴ�.
				// �� ��� ������ �޼����� ó�� �� �ش� �۾��� �մϴ�.
				// �ش� �۾��� ��� ������ �׵��� �׿��ִ� �޼����� ó���մϴ�.
<<<<<<< HEAD
<<<<<<< HEAD

				if ( (gMode == eMode::MD_ING) && (bIsFirstEnter) )
				{
					static std::shared_ptr<MyPoint> pos = std::make_shared<MyPoint>();
					if (bServer)
					{
						if (bBlackTurn)
						{
							// ���� ���� ������ ���
							// Ÿ�̸Ӹ� �����մϴ�.
							//SET_TIMER(BEGIN_TIME);
							bIsFirstEnter = false;
							continue;
						}
						else
						{
							// Ÿ�̸Ӹ� �����ϰ� 
							// ��밡 ���� ���� ���� ��ǥ��
							// ������ ������ ��ٸ��ϴ�.
							// �׷��� ���� �����尡 ���ŷ�Ǹ� �ȵǹǷ�
							// recv�� ����� �����带 �����մϴ�.
							//SET_TIMER(BEGIN_TIME);

							bIsFirstEnter = false;
							HANDLE tHandle = (HANDLE)_beginthreadex(nullptr, 0, RecvPosFromClient, static_cast<void*>(&pos), 0, nullptr);
							CloseHandle(tHandle);							
						}
					}
					else
					{
						if (bBlackTurn)
						{
							// Ÿ�̸Ӹ� �����ϰ� 
							// ��밡 ���� ���� ���� ��ǥ��
							// ������ ������ ��ٸ��ϴ�.
							// �׷��� ���� �����尡 ���ŷ�Ǹ� �ȵǹǷ�
							// recv�� ����� �����带 �����մϴ�.
							//SET_TIMER(BEGIN_TIME);

							bIsFirstEnter = false;
							HANDLE tHandle = (HANDLE)_beginthreadex(nullptr, 0, RecvPosFromServer, static_cast<void*>(&pos), 0, nullptr);
							CloseHandle(tHandle);
						}
						else
						{
							//SET_TIMER(BEGIN_TIME);
							bIsFirstEnter = false;
							continue;
						}
					}
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
				//Render();

				if ( bReadyP1 && bReadyP2 && (gMode == eMode::MD_BEFORE_START) )
				{
					MessageBox(ghWnd, L"���� ����!", NULL, MB_OK);
					gMode = eMode::MD_ING;
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
				}
			}
		}

		return 0;
	}




	/*----------------------------------------------------------------------------------
		Name: WndProc()
		Desc: �ü���� ���� ȣ��Ǵ� �Լ��� �޼����� ó���մϴ�.
	----------------------------------------------------------------------------------*/
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_CREATE:
<<<<<<< HEAD
<<<<<<< HEAD
			{
				CreateStartMenu(hWnd);
				InitGlobalVariables(hWnd);
				return 0;
			}
=======
				CreateStartMenu(hWnd);
				InitGlobalVariables(hWnd);
				return 0;
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
				CreateStartMenu(hWnd);
				InitGlobalVariables(hWnd);
				return 0;
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

			case WM_DESTROY:
				SAFE_CLEANUP(gdiplusToken);
				PostQuitMessage(0);
				return 0;

			// ��ư Ŭ�� ó��
			case WM_COMMAND:
				switch (LOWORD(wParam))
				{
					case BT_CREATE_ROOM:  // �� ���� ��ư (It will be a host)
					{
						HANDLE tHandle = (HANDLE)_beginthreadex(NULL, 0, CreateRoom, nullptr, 0, 0); // ������ ������
						CloseHandle(tHandle);
						return 0;
					}
					
					case BT_ENTER_ROOM:   // ���� �� ���� ��ư (It will be a client)  
					{
						HANDLE tHandle = (HANDLE)_beginthreadex(NULL, 0, JoinRoom, nullptr, 0, 0);
						CloseHandle(tHandle);
						return 0;
					}

					case BT_EXIT:		  // ���� ���� ��ư
					{
						if (gMode != eMode::MD_ING) // ���� ���� ���� �ƴ� ��츸 Ŭ�� ����
						{
							DestroyWindow(hWnd);
						}
						return 0;
					}

					case BT_READY: // Ready ��ư
					{
						// Ŭ�� �� bReady ������ ������Ű��
						// ��뿡�� ��ȣ�� �����ϴ�.
						Assert(gSocket != NULL, "gSocket must not be NULL.");

						EnterCriticalSection(&cs);
<<<<<<< HEAD
<<<<<<< HEAD
						if (!bServer)
						{
							bReadyP2 = !bReadyP2;
						}

						gReadyMngForSend->SendSignal(gSocket);
						LeaveCriticalSection(&cs);

						textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P2_ID_X, PI_P_ID_Y + 50, PI_P_ID_WIDTH, PI_P_ID_HEIGHT + 30, "READY"));
						PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);

=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

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
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
						return 0;
					}

					case BT_START: // ���� ���� ��ư
					{
<<<<<<< HEAD
<<<<<<< HEAD
						Assert(gSocket != NULL, "gSocket must not be NULL.");
						if (bServer)
						{
							// ��뿡�� ���� ���� ��ȣ�� �����ϴ�.
							SignalManager startMng(SignalManager::eSignal::SIG_START);
							startMng.SendSignal(gSocket);
						}

=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
						return 0;
					}
				}
				return 0;

<<<<<<< HEAD
<<<<<<< HEAD
			// ���콺 Ŭ�� ó��
			case WM_LBUTTONUP:
				if (gMode == eMode::MD_ING)
				{
					if ((bServer && bBlackTurn) || (!bServer && !bBlackTurn))
					{
						static std::shared_ptr<MyPoint> pos;
						pos.reset();

						if (IsValidPos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), &pos))
						{
							// Ŭ���� ��ġ�� �ٵϵ��� ����
							// Ÿ�̸Ӹ� ���� ��
							// �ٵϵ� ��ġ�� ��뿡�� �����մϴ�.
							auto bSuccess = PutStone(pos);
							if (!bSuccess)
							{
								// �������� ��ġ�� ���� Ŭ����
								// ��ȿ ó���մϴ�.
								return -1;
							}

							KillTimer(ghWnd, 1);
							bErase = true;
							if (bServer)
							{
								InvalidateRect(ghWnd, &timeRT_P1, true);

								// ���� ���� �� �¸� ������ üũ�մϴ�.
								if (gBlackStoneCount >= 5 && CheckWinCondition('b'))
								{
									// ���� ���� �� ��ƾ�� �ۼ��մϴ�.
									bIsFirstEnter = false;
									gMode = eMode::MD_END;
									SendGameResult(true, pos); // P1�� �¸��� ����� �۽��մϴ�.
									MessageBoxW(hWnd, L"You WIN!", L"Result", MB_OK);
								}
								else
								{
									// �¸� ������ �������� ���ߴٸ� 
									// ���� ���� ��ǥ�� ��뿡�� �۽��մϴ�.
									SET_TIMER(BEGIN_TIME);
									HANDLE tHandle = (HANDLE)_beginthreadex(nullptr, 0, SendPosToClient, static_cast<void*>(&pos), 0, nullptr);
									CloseHandle(tHandle);
									bBlackTurn = false;
									bIsFirstEnter = true;
								}
							}
							else
							{
								SET_TIMER(BEGIN_TIME);
								InvalidateRect(ghWnd, &timeRT_P2, true);

								HANDLE tHandle = (HANDLE)_beginthreadex(nullptr, 0, SendPosToServer, static_cast<void*>(&pos), 0, nullptr);
								CloseHandle(tHandle);

								bBlackTurn = true;
								bIsFirstEnter = true;
							}

							//UpdateWindow(ghWnd);
						}
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
			case WM_LBUTTONUP:
				if (gMode == eMode::MD_ING)
				{
					std::unique_ptr<MyPoint> pos;
					if (IsValidPos(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), &pos))
					{
						PutStone(std::move(pos));
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
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
<<<<<<< HEAD
<<<<<<< HEAD
				OnPaint();
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
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
								// ��� �������� ��� �׸��ϴ�.
								DrawPlayerPlace(hdc, PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT);
								DrawMyImage(gBoardImgPtr, hdc, (float)BD_BEGIN_X, (float)BD_BEGIN_Y, (float)BD_WIDTH, (float)BD_HEIGHT);
								DrawMyImage(gPlayer1ImgPtr, hdc, (float)(PP1_X + 45), (float)(PP_Y + 45), (float)150, (float)450);
								break;
							}

							case ePhase::PH_SERVER_2:
							{
								// ��� �������� ��� �׸��ϴ�.
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
								// ��� �������� ��� �׸��ϴ�.
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
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
				return 0;
			}



			/*************************** 
				   CUSTOM MESSGAE
			***************************/
			
			case MSG_DELETE_START_MENU: // ���� �޴��� ����ϴ�.
				DeleteStartMenu();
				UpdateWindow(hWnd);
				return 0;

			case MSG_DRAW_IMAGE:	    // �̹����� �׸��ϴ�.
			{
				while(!imageInfoQueue.empty())
				{
					auto imageInfo = imageInfoQueue.front();
					imageInfoQueue.pop();
					DrawMyImage(imageInfo->Image, gHdc, imageInfo->X, imageInfo->Y, imageInfo->Width, imageInfo->Height);
				}
				return 0;
			}
<<<<<<< HEAD
<<<<<<< HEAD
			
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
			case MSG_DRAW_PLAYER_PLACE: // �÷��̾� ������ �׸��ϴ�.
			{
				while (!ppInfoQueue.empty())
				{
					auto ppInfo = ppInfoQueue.front(); // shared_ptr
					ppInfoQueue.pop();
					DrawPlayerPlace(gHdc, ppInfo->X, ppInfo->Y, ppInfo->Width, ppInfo->Height);
				}
				return 0;
			}

			case MSG_DRAW_BUTTON:	    // ��ư�� �׸��ϴ�.
			{
				while (!btnInfoQueue.empty())
				{
					auto btnInfo = btnInfoQueue.front(); // shared_ptr
					btnInfoQueue.pop();
					DrawButton(btnInfo->X, btnInfo->Y, btnInfo->Width, btnInfo->Height, btnInfo->ButtonID, btnInfo->ButtonName);
				}
				return 0;
			}

			case MSG_DRAW_TEXT:		// �ؽ�Ʈ�� �׸��ϴ�.
			{
				while (!textInfoQueue.empty())
				{
<<<<<<< HEAD
<<<<<<< HEAD
					static const auto COL_DEFAULT = RGB(0, 0, 0);
					static const auto COL_RED     = RGB(255, 0, 0);
					static const auto COL_SKY     = COLORREF(0x00d1b499);

					SetBkColor(gHdc, COL_SKY);

					auto textInfo = textInfoQueue.front(); // shared_ptr
					textInfoQueue.pop();
					if (textInfo->Text == "READY") // Ready ��ư�� Ŭ���� ������ READY ǥ�ø� ON/OFF
					{
						static bool bShow = true;
						bShow ? SetTextColor(gHdc, COL_RED) : SetTextColor(gHdc, COL_SKY);
						bShow = !bShow;
					}
					DrawMyText(gHdc, textInfo->X, textInfo->Y, textInfo->Width, textInfo->Height, textInfo->Text);
				}
				return 0;
			}

			// ��밡 ���� ������ �� �����ϴ� �޼����Դϴ�.
			// �� ������ ���� ���� �׸��� ��ƾ�� �����մϴ�.
			// RecvPosFromServer Ȥ�� RecvPosFromClient���� 
			// ������ ���� �� �� �޼����� �۽��մϴ�.
			case MSG_DRAW_STONE:
			{
				static Graphics g(gHdc_bStone);

				auto pos = *(reinterpret_cast<std::shared_ptr<MyPoint>*>(wParam));

				if (!bServer)
				{
					Assert(bBlackTurn, "It must be a black's turn!");

					// �������� ���� ��ǥ�� ���� �� �׸��ϴ�.
					// �� �������� �۽��� ��ǥ�� Client���� �׸��ϴ�.
					g.DrawImage(gBlackStoneImgPtr, pos->X.first, pos->Y.first, ST_LENGTH, ST_LENGTH);
					board[pos->X.second][pos->Y.second] = 'b';

					BYTE gameoverInfo = *(reinterpret_cast<BYTE*>(lParam));
					if ((bool)GET_GAMEOVER(gameoverInfo))
					{
						KillTimer(ghWnd, 1);
						bIsFirstEnter = false;
						gMode = eMode::MD_END;

						// ������ ������ ���
						(bool)GET_WINNER(gameoverInfo) ? 
							MessageBox(hWnd, L"You LOSE!", L"Result", MB_OK) : MessageBox(hWnd, L"You WIN!", L"Result", MB_OK);

						return 0;
					}
				}
				else
				{
					Assert(!bBlackTurn, "It must be a server's turn!");

					// ���� ���� ��ǥ�� ���� �� �׸��ϴ�.
					// �� Client���� �۽��� ��ǥ�� �������� �׸��ϴ�.
					g.DrawImage(gWhiteStoneImgPtr, pos->X.first, pos->Y.first, ST_LENGTH, ST_LENGTH);
					board[pos->X.second][pos->Y.second] = 'w';
					++gWhiteStoneCount;

					// ��밡 ���� ���� ��ǥ�� ���� ��
					// �¸� ������ üũ�մϴ�.
					if (gWhiteStoneCount >= 5 && CheckWinCondition('w'))
					{
						// �¸� �� ��ƾ �ۼ�
						KillTimer(ghWnd, 1);
						bIsFirstEnter = false;
						gMode = eMode::MD_END;
						SendGameResult(false, pos);
						MessageBoxW(hWnd, L"You LOSE!", L"Result", MB_OK);

						return 0;
					}
				}

				// ��� Ÿ�̸� ���� �� �� Ÿ�̸Ӹ� �����մϴ�.
				KillTimer(ghWnd, 1);
				SET_TIMER(BEGIN_TIME);
				bErase = true;
				(bBlackTurn) ? InvalidateRect(ghWnd, &timeRT_P1, true) : InvalidateRect(ghWnd, &timeRT_P2, true);
				bBlackTurn = !bBlackTurn;
				bIsFirstEnter = true;
				//UpdateWindow(ghWnd);

				return 0;
			}

		} // switch

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}


	VOID OnPaint()
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(ghWnd, &ps);

		// ���� ���� ���� ���
		if (gMode == eMode::MD_ING)
		{
			if (gPhase == ePhase::PH_ING)
			{
				if (bErase)
				{
					bErase = false;
					EndPaint(ghWnd, &ps);
					return;
				}

				static char timeString[3]; // "0 ~ "60"
				_itoa_s(gTimeLimit, timeString, 10);

				// �� �Ͽ� �°� �ð��� ����մϴ�.
				if (bBlackTurn)
				{
					DrawTextA(gHdc, timeString, strlen(timeString), &timeRT_P1, DT_CENTER);
				}
				else
				{
					DrawTextA(gHdc, timeString, strlen(timeString), &timeRT_P2, DT_CENTER);
				}
			}
		}
		else if (gMode >= eMode::MD_BEFORE_START)
		{
			if (bServer)
			{
				switch (gPhase)
				{
					case ePhase::PH_SERVER_1:
					{
						// ��� �������� ��� �׸��ϴ�.
						DrawPlayerPlace(hdc, PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT);
						DrawMyImage(gBoardImgPtr, hdc, (float)BD_BEGIN_X, (float)BD_BEGIN_Y, (float)BD_WIDTH, (float)BD_HEIGHT);
						DrawMyImage(gPlayer1ImgPtr, hdc, (float)(PP1_X + 45), (float)(PP_Y + 45), (float)150, (float)450);
						break;
					}

					case ePhase::PH_SERVER_2:
					{
						// ��� �������� ��� �׸��ϴ�.
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
						// ��� �������� ��� �׸��ϴ�.
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

		EndPaint(ghWnd, &ps);
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
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
		Desc: SetTimer �Լ��� ������ ���� �ð����� �ü���� ���� ȣ��Ǵ� �ݹ� �Լ��Դϴ�.
	----------------------------------------------------------------------------------*/
	VOID CALLBACK MyTimeProc(HWND hWnd, UINT nMsg, UINT_PTR nlDEvent, DWORD dwTime)
	{

	}




	/*----------------------------------------------------------------------------------
		Name: InitD3D()
		Desc: Direct3D�� �ʱ�ȭ�մϴ�.
	----------------------------------------------------------------------------------*/
	HRESULT InitD3D(HWND hWnd)
	{
		// D3D ��ü�� �����մϴ�.
		gD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (gD3D == NULL)
		{
			return E_FAIL;
		}

		// D3D ����̽� ������ ���� ������ ����
		D3DPRESENT_PARAMETERS d3dpp = {};
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		// D3D ����̽� ��ü ����
		if (FAILED( gD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp, &gD3D_Device )))
		{
			gD3D->Release();
			gD3D = nullptr;
			return E_FAIL;
		}

		// ��������Ʈ ��ü ����
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
		Desc: �ؽ��ĸ� �����ϰ� �ʱ�ȭ�մϴ�.
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
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	}



<<<<<<< HEAD
<<<<<<< HEAD
	/*----------------------------------------------------------------------------------
		Name: MyTimeProc()
		Desc: SetTimer �Լ��� ������ ���� �ð����� �ü���� ���� ȣ��Ǵ� �ݹ� �Լ��Դϴ�.
	----------------------------------------------------------------------------------*/
	VOID CALLBACK MyTimeProc(HWND hWnd, UINT msg, UINT_PTR idTimer, DWORD dwTime)
	{
		if (idTimer == 1)
		{
			if (gTimeLimit > 0)
			{
				// Ÿ�̸Ӱ� �����Ǹ�
				// ���� ȣ��Ǹ� ���� �ð��� �����մϴ�.
				--gTimeLimit; 
			}
			else
			{
				// �ð��� 0�� �Ǹ� �й� ó��
				KillTimer(hWnd, 1);
				bIsFirstEnter = false;
				gMode = eMode::MD_END;

				// ������ ��� ��뿡�� ���� ����� �����մϴ�.
				if (bServer)
				{
					if (bBlackTurn)
					{
						SendGameResult(false);
						MessageBoxW(hWnd, L"You LOSE!", L"Result", MB_OK);
					}
					else
					{
						SendGameResult(true);
						MessageBoxW(hWnd, L"You WIN!", L"Result", MB_OK);
					}
				}
				else
				{
					if (!bBlackTurn)
					{
						bIsFirstEnter = false;
						gMode = eMode::MD_END;
						MessageBoxW(hWnd, L"You LOSE!", L"Result", MB_OK);
					}
				}

				return;
			}

			bBlackTurn ? InvalidateRect(hWnd, &timeRT_P1, TRUE) : InvalidateRect(hWnd, &timeRT_P2, TRUE);
		}

		return;
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	/*----------------------------------------------------------------------------------
		Name: Render()
		Desc: ����� �׸��ϴ�.(������)
	----------------------------------------------------------------------------------*/
	VOID Render()
	{
		if (gD3D_Device == NULL || gD3D_Sprite == NULL)
		{
			return;
		}

		gD3D_Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 160), 1.f, 0);

		// ����� �׻� �ĸ� ���ۿ� �׸��ϴ�.
		// ����� ����̽��� BeginScene() �Լ��� EndScene() �Լ� ���̿��� �׷��� �մϴ�.
		// ���� ��������Ʈ ��ü�� Draw()�� ���ؼ� Begin()�� End() ���̿� ȣ���ؾ� �մϴ�.

		//RECT rt = { 0, 0, 1024, 768 };
		if (SUCCEEDED(gD3D_Device->BeginScene()))
		{
			gD3D_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
			gD3D_Sprite->Draw(gTexture, NULL, NULL, NULL, D3DXCOLOR(1, 1, 1, 1));
			gD3D_Sprite->End();

			gD3D_Device->EndScene();
		}

		// ������ۿ� �ĸ���۸� ��ü�մϴ�.
		gD3D_Device->Present(NULL, NULL, NULL, NULL);
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	}



<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	/*----------------------------------------------------------------------------------
		Name: CleanUp()
		Desc: �ʱ�ȭ�� ��ü �� �����͸� �����մϴ�.
	----------------------------------------------------------------------------------*/
	VOID CleanUp()
	{
<<<<<<< HEAD
<<<<<<< HEAD
		KillTimer(ghWnd, 1);
		GdiplusShutdown(gdiplusToken);
		ReleaseDC(ghWnd, gHdc);
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		GdiplusShutdown(gdiplusToken);
		ReleaseDC(ghWnd, gHdc);
		SAFE_RELEASE(gTexture);
		SAFE_RELEASE(gD3D_Sprite);
		SAFE_RELEASE(gD3D_Device);
		SAFE_RELEASE(gD3D);
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	}




	/*----------------------------------------------------------------------------------
		Name: InitGameData()
		Desc: ���� �����͸� �ʱ�ȭ�մϴ�.
	----------------------------------------------------------------------------------*/
	HRESULT InitGameData(HWND hWnd)
	{
		// GDI+ �ʱ�ȭ
		if (::Status::Ok != GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL))
		{
			return E_FAIL;
		}

		// ��ǥ ���� �� �ʱ�ȭ
		InitCoordinate();

		return S_OK;
	}


	
	
	/*----------------------------------------------------------------------------------
		Name: InitStartMenu()
		Desc: ���� ȭ���� �����մϴ�.
	----------------------------------------------------------------------------------*/
	VOID CreateStartMenu(HWND hWnd)
	{
		for (size_t i = 0; i < BT_COUNT; ++i)
		{
			gStartMenuBtns[i] = CreateWindow(L"button", gButtonNames[i], BT_MENU_STYLE,
				BTN_X, BTN_Y + (BTN_DISTANCE * i), BTN_WIDTH, BTN_HEIGHT, hWnd, (HMENU)i, ghInst, NULL);
		}

		// ShowWindow() �Լ��� WM_PAINT �޼����� TRUE�� �����մϴ�.
		// �׷��� �̿� ���� ó���� ��� �޼��� ť�� ��� �޼�����
		// ��� ó���ϰ� ���� �ϱ� ������ �켱������ �����ϴ�.
		// UpdateWindow() �Լ��� ���� ��� WndProc�Լ��� WM_PAINT ó���� ��û�մϴ�.
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}




	/*----------------------------------------------------------------------------------
		Name: DeleteStartMenu()
		Desc: ���� ȭ���� �����մϴ�.
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
		Desc: ���� ȭ���� �ε��մϴ�.
	----------------------------------------------------------------------------------*/
	VOID LoadGameScreen()
	{
		// �۾� ť�� �����͸� �߰��մϴ�.
		if (bServer)
		{
			ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT));
<<<<<<< HEAD
<<<<<<< HEAD
			btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_P1_READY_X, IGB_READY_Y, IGB_READY_WIDTH, IGB_READY_HEIGHT, (HMENU)(BT_START), L"Game Start")); // player1 ���� ��ư
=======
			btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_P1_READY_X, IGB_READY_Y, IGB_READY_WIDTH, IGB_READY_HEIGHT, (HMENU)(BT_READY), L"Ready")); // player1 �غ� ��ư
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
			btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_P1_READY_X, IGB_READY_Y, IGB_READY_WIDTH, IGB_READY_HEIGHT, (HMENU)(BT_READY), L"Ready")); // player1 �غ� ��ư
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
			textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P1_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer1Ptr->GetID())); // Player1 ID  
		}
		else
		{
			ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP1_X, PP_Y, PP_WIDTH, PP_HEIGHT));
			ppInfoQueue.emplace(std::make_shared<InGamePPInfo>(PP2_X, PP_Y, PP_WIDTH, PP_HEIGHT));
			btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_P2_READY_X, IGB_READY_Y, IGB_READY_WIDTH, IGB_READY_HEIGHT, (HMENU)(BT_READY), L"Ready")); // player2 �غ� ��ư
			imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER2_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer2ImgPtr)); // ĳ����2
			textInfoQueue.emplace(std::make_shared<TextInfo>(PI_P2_ID_X, PI_P_ID_Y, PI_P_ID_WIDTH, PI_P_ID_HEIGHT, gPlayer2Ptr->GetID())); // Player2 ID  
		}

		btnInfoQueue.emplace(std::make_shared<InGameButtonInfo>(IGB_EXIT_X, IGB_EXIT_Y, IGB_EXIT_WIDTH, IGB_EXIT_HEIGHT, (HMENU)(BT_EXIT), L"Exit")); // Exit ��ư
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)BD_BEGIN_X, (float)BD_BEGIN_Y, (float)BD_WIDTH, (float)BD_HEIGHT, gBoardImgPtr)); // ������
<<<<<<< HEAD
<<<<<<< HEAD
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER1_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer1ImgPtr)); // ĳ����1
=======
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER1_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer1ImgPtr));       // ĳ����1
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
		imageInfoQueue.emplace(std::make_shared<ImageInfo>((float)PI_PLAYER1_X, (float)PI_PLAYER_Y, (float)PI_PLAYER_WIDTH, (float)PI_PLAYER_HEIGHT, gPlayer1ImgPtr));       // ĳ����1
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

		// UI �����尡 ť�� ����� �����͸� ó���ϵ��� �մϴ�.
		PostMessage(ghWnd, MSG_DRAW_PLAYER_PLACE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_BUTTON, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_IMAGE, NULL, NULL);
		PostMessage(ghWnd, MSG_DRAW_TEXT, NULL, NULL);
	}




	/*----------------------------------------------------------------------------------
		Name: InitCoordinate()
		Desc: �������� �� �������� �����ϴ� 2���� �迭�� �ʱ�ȭ�մϴ�.
	----------------------------------------------------------------------------------*/
	VOID InitCoordinate()
	{
		coordinate_type startX = BD_BEGIN_COORDI_X;
		coordinate_type startY = BD_BEGIN_COORDI_Y;

		xPos.reserve(BD_LENGTH);
		yPos.reserve(BD_LENGTH);

		for (size_t i = 0; i < BD_LENGTH; ++i)
		{
			// ������ �ʱ�ȭ
			board[i] = std::make_unique<char[]>(BD_LENGTH); 

			xPos.emplace_back(std::make_pair(startX, i));
			yPos.emplace_back(std::make_pair(startY, i));
			startX += BD_DISTANCE_DOT_TO_DOT;
			startY += BD_DISTANCE_DOT_TO_DOT;
		}
	}



	/*----------------------------------------------------------------------------------
		Name: IsValidPos()
		Desc: (x, y)�� ��ȿ�� ��ǥ���� Ȯ�� �� �ش� ��ǥ�� ������ �������� ��ǥ�� ��ȯ�մϴ�.
	----------------------------------------------------------------------------------*/
<<<<<<< HEAD
<<<<<<< HEAD
	bool IsValidPos(WORD x, WORD y, std::shared_ptr<MyPoint>* pOut)
=======
	bool IsValidPos(WORD x, WORD y, std::unique_ptr<MyPoint>* pOut)
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
	bool IsValidPos(WORD x, WORD y, std::unique_ptr<MyPoint>* pOut)
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	{
		// �ٵϵ��� ��Ȯ�� �� ���������� �������ϴ�.
		// ������ ���Ǽ��� ���� ���� �Ÿ� �̳��� ������ Ŭ���ص�
		// ��ȿ�� Ŭ������ �Ǵ��ϸ�, Ŭ���� ��ǥ�� ������ �������� pOut�� �����մϴ�.
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

		// ��ȿ�� ��ǥ
		return false;
	}




	/*----------------------------------------------------------------------------------
		Name: PutStone()
		Desc: pos�� ����Ű�� ��ġ�� �ٵϵ��� �����ϴ�.
	----------------------------------------------------------------------------------*/
<<<<<<< HEAD
<<<<<<< HEAD
	bool PutStone(const std::shared_ptr<MyPoint> pos)
	{
		// �ٵϵ� �̹����� �����մϴ�.
		static const char BLACK_STONE = 'b';
		static const char WHITE_STONE = 'w';
		
		// pos�� ����Ű�� ��ǥ�� ���� �߾��� �ǵ��� �մϴ�.
		// �ٵϵ��� �����Ͱ� ������ ����� �迭�� �ε����� �����ɴϴ�.
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	VOID PutStone(const std::unique_ptr<MyPoint> pos)
	{
		// �ٵϵ� �̹����� �����մϴ�.
		static std::unique_ptr<Image> blackStoneImg(Image::FromFile(IMG_BlackStone));
		static std::unique_ptr<Image> whiteStoneImg(Image::FromFile(IMG_WhiteStone));
		static HDC hdc_blackStn = GetDC(ghWnd);
		static HDC hdc_whiteStn = GetDC(ghWnd);
		const char BLACK_STONE = 'b';
		const char WHITE_STONE = 'w';
		
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		coordinate_type x      = TO_CENTER(pos->X.first);
		coordinate_type y      = TO_CENTER(pos->Y.first);
		idx_type        row    = pos->Y.second;
		idx_type        column = pos->X.second;

		// �̹� ���� ���� ���̸� ��ȿȭ�մϴ�.
		if (board[row][column] != NULL)
		{
<<<<<<< HEAD
<<<<<<< HEAD
			return false;
		}
		
		// �ٵϵ��� �����ϴ�.
		if (bServer)
		{
			Assert(bBlackTurn, "it must be black's turn.");

			static Graphics g(gHdc_bStone);
			g.DrawImage(gBlackStoneImgPtr, x, y, ST_LENGTH, ST_LENGTH);
			board[row][column] = BLACK_STONE;
			++gBlackStoneCount;
		}
		else
		{
			Assert(!bBlackTurn, "it must be white's turn.");

			static Graphics g(gHdc_wStone);
			g.DrawImage(gWhiteStoneImgPtr, x, y, ST_LENGTH, ST_LENGTH);
			board[row][column] = WHITE_STONE;
		}

		bBlackTurn = !bBlackTurn;
		return true;
=======
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
			return;
		}
		
		// �ٵϵ��� �����ϴ�.
		if (pos->IsBlack)
		{
			Graphics g(hdc_blackStn);
			g.DrawImage(blackStoneImg.get(), x, y, ST_LENGTH, ST_LENGTH);
			board[row][column] = BLACK_STONE;
			++gBlackStoneCount;

			// ���� 5�� �̻� ������ ��� �˻��մϴ�.
			if (gBlackStoneCount >= 5)
			{
				// �������� �¸� ������ Ȯ���մϴ�.
				if (CheckWinCondition(BLACK_STONE) == true)
				{
					MessageBoxW(NULL, L"������ ��", NULL, MB_OK);
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
					MessageBoxW(NULL, L"�� ��", NULL, MB_OK);
				}
			}
		}

		bBlackTurn = !bBlackTurn;
<<<<<<< HEAD
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	}




	/*----------------------------------------------------------------------------------
		Name: CheckWinCondition()
		Desc: stone�� ���� �¸� ������ �����Ͽ����� Ȯ���մϴ�.
	----------------------------------------------------------------------------------*/
	bool CheckWinCondition(char stone)
	{
		for (idx_type row = 0; row < BD_LENGTH; ++row)
		{
			for (idx_type col = 0; col < BD_LENGTH; ++col)
			{
				if (board[row][col] == stone)
				{
					// ��ס�� ���� üũ�� �մϴ�.
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



	// �������� �׷��ݴϴ�.
	VOID DrawMyImage(Gdiplus::Image* pImage, HDC hdc, float x, float y, float width, float height)
	{
		::Graphics g(hdc);
		g.DrawImage(pImage, x, y, width, height);
	}


	// �÷��̾� ������ �׷��ݴϴ�.
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

<<<<<<< HEAD
<<<<<<< HEAD
		Assert(btn_hWnd != NULL, "Failed to CreateWindow() in DrawButton()");

=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		switch (eBtnID)
		{
		case BT_READY:
			gReadyBtn = btn_hWnd;
			return 0;

		case BT_START:
			gStartBtn = btn_hWnd;
			return 0;
<<<<<<< HEAD
<<<<<<< HEAD

		case BT_EXIT:
			gExitBtn = btn_hWnd;
			return 0;
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
		}

		return btn_hWnd;
	}


	inline VOID DrawMyText(HDC hdc, long x, long y, long width, long height, const char* text)
	{
		RECT rc = { x, y, x + width, y + height };
		DrawTextA(hdc, text, strlen(text), &rc, DT_CENTER);
	}


<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	VOID SendPlayerInfo(SOCKET sock, std::shared_ptr<PlayerInfo> info)
	{
		OutputMemoryStream ostream;
		info->Write(ostream); // info�� �� ����� ostream�� ����ȭ�մϴ�.

		send(sock, ostream.GetBuffer(), ostream.GetSize(), 0);
	}


<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	// recv�� ���� ����ȭ�� �����͸� ������ȭ�Ͽ� info�� �о���Դϴ�.
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

<<<<<<< HEAD
<<<<<<< HEAD

	// ���� ����� ����ȭ �� ��뿡�� �����մϴ�.
	// ���� pos�� NULL�� ��� �ð� �ʰ��� ���� �й��̹Ƿ�
	// ��ǥ�� �������� �ʽ��ϴ�.
	unsigned SendGameResult(bool bIsPlayer1Win, std::shared_ptr<MyPoint> pos)
	{
		BYTE gameoverInfo;
		CLEAR_PACKET(gameoverInfo);
		SET_GAMEOVER(gameoverInfo, true);
		SET_WINNER(gameoverInfo, bIsPlayer1Win);
		
		if (pos.get() == nullptr)
		{
			SET_TIMEOVER(gameoverInfo);

			OutputMemoryStream ostream;
			ostream.WriteInBuffer(gameoverInfo); // info   (1byte)

			auto sendBytes = send(gSocket, ostream.GetBuffer(), ostream.GetSize(), 0);
			if (sendBytes > 0)
			{
				return sendBytes;
			}
			else
			{
				Assert(false, "Failed to SendPosFromServer()");
				return NULL;
			}
		}

		coordinate_type x      = TO_CENTER(pos->X.first);
		coordinate_type y      = TO_CENTER(pos->Y.first);
		idx_type        row    = pos->Y.second;
		idx_type        column = pos->X.second;

		OutputMemoryStream ostream;
		ostream.WriteInBuffer(gameoverInfo); // info   (1byte)
		ostream.WriteInBuffer(x);            // x      (2bytes)
		ostream.WriteInBuffer(y);            // y      (2bytes)
		ostream.WriteInBuffer(row);          // row    (1byte)
		ostream.WriteInBuffer(column);       // column (1byte)

		auto sendBytes = send(gSocket, ostream.GetBuffer(), ostream.GetSize(), 0);
		if (sendBytes > 0)
		{
			return sendBytes;
		}
		else
		{
			Assert(false, "Failed to SendPosFromServer()");
		}

		return NULL;
	}


	// ��뿡�� ��ǥ�� �����մϴ�.
	unsigned __stdcall SendPosToClient(void* pArg)
	{
		// Client���� ��Ŷ�� �����մϴ�.
		// ��Ŷ�� <������ ���� ����> + <��ǥ>�� �����˴ϴ�.
		auto pos = *(static_cast<std::shared_ptr<MyPoint>*>(pArg));

		BYTE gameoverInfo;
		CLEAR_PACKET(gameoverInfo);
		SET_GAMEOVER(gameoverInfo, false);

		coordinate_type x      = TO_CENTER(pos->X.first); // 2bytes
		coordinate_type y      = TO_CENTER(pos->Y.first); // 2bytes
		idx_type        row    = pos->Y.second;			  // 1byte
		idx_type        column = pos->X.second;			  // 1byte

		static OutputMemoryStream ostream;
		ostream.ClearBuffer();
		Assert(ostream.GetSize() == 0, "ostream must be empty!");

		// �����͸� ����ȭ�մϴ�.
		ostream.WriteInBuffer(gameoverInfo); // 1byte
		ostream.WriteInBuffer(x);		     // 2bytes	
		ostream.WriteInBuffer(y);		     // 2bytes
		ostream.WriteInBuffer(row);			 // 1byte
		ostream.WriteInBuffer(column);		 // 1byte

		auto sendBytes = send(gSocket, ostream.GetBuffer(), ostream.GetSize(), 0);
		if (sendBytes > 0)
		{
			return sendBytes;
		}
		else
		{
			Assert(false, "Failed to SendPosFromServer()");
		}

		return NULL;
	}

	unsigned __stdcall SendPosToServer(void* pArg)
	{
		// Ŭ���̾�Ʈ���� ������ ������ �� �ʿ��� ��ǥ��
		// �ٵϵ��� ���� ��ǥ�� �׿� �����ϴ� board�� 2���� �迭 �ε����Դϴ�.
		auto pos = *(static_cast<std::shared_ptr<MyPoint>*>(pArg));

		coordinate_type x      = TO_CENTER(pos->X.first);
		coordinate_type y      = TO_CENTER(pos->Y.first);
		idx_type        row    = pos->Y.second;
		idx_type        column = pos->X.second;

		static OutputMemoryStream ostream;
		ostream.ClearBuffer();
		Assert(ostream.GetSize() == 0, "ostream must be empty!");

		// �����͸� ����ȭ�մϴ�.
		ostream.WriteInBuffer(x);
		ostream.WriteInBuffer(y);
		ostream.WriteInBuffer(row);
		ostream.WriteInBuffer(column);

		auto sendBytes = send(gSocket, ostream.GetBuffer(), ostream.GetSize(), 0);
		if (sendBytes > 0)
		{
			return sendBytes;
		}
		else
		{
			Assert(false, "Failed to SendPosFromServer()");
		}

		return NULL;
	}

	unsigned __stdcall RecvPosFromServer(void* pArg)
	{
		// 7����Ʈ�� ����ȭ�� ��Ŷ�� �����մϴ�.
		// gameoverInfo (1byte)  : ���� 4��Ʈ�� ���� ���� ����, ���� 4��Ʈ�� Winner(1: p1, 0: p2)
		// x            (2bytes) 
		// y            (2bytes)  
		// row          (1byte)	  
		// column       (1byte)	  

		static const size_t MAX_BYTES = 7;
		static InputMemoryStream istream(MAX_BYTES);
		Assert(istream.GetBufferPtr() != nullptr, "buffer need to memory allocation.");

		std::shared_ptr<MyPoint> pos;

		istream.ClearBuffer();
		int recvBytes = recv(gSocket, istream.GetBufferPtr(), MAX_BYTES, 0);
		if (recvBytes > 0)
		{
			// ù ����Ʈ�� �о�ɴϴ�.
			BYTE gameoverInfo;
			istream.ReadFromBuffer(&(gameoverInfo));

			// Ÿ�� �ƿ� ��
			if ((BYTE)GET_GAMEOVER(gameoverInfo) == 0x0f)
			{
				// �ð� �ʰ��� ���� ���� ����
				KillTimer(ghWnd, 1);
				bIsFirstEnter = false;
				(bool)GET_WINNER(gameoverInfo) ?
					MessageBox(ghWnd, L"You LOSE!", L"Result", MB_OK) : MessageBox(ghWnd, L"You WIN!", L"Result", MB_OK);

				return static_cast<unsigned>(recvBytes);
			}
			
			pos = *(static_cast<std::shared_ptr<MyPoint>*>(pArg));

			istream.ReadFromBuffer(&(pos->X.first));  // x    (2bytes)
			istream.ReadFromBuffer(&(pos->Y.first));  // y    (2bytes)
			istream.ReadFromBuffer(&(pos->X.second)); // row  (1byte)
			istream.ReadFromBuffer(&(pos->Y.second)); // col  (1byte)

			// �������� ���� ���� ����
			if ((bool)GET_GAMEOVER(gameoverInfo))
			{
				KillTimer(ghWnd, 1);
				bIsFirstEnter = false;
			}

			// ** PostMessage�� �����ϴ� ���� ���� �޶��� �� �־� ���X **
			SendMessage(ghWnd, MSG_DRAW_STONE, (WPARAM)&pos, (LPARAM)&gameoverInfo);
		}
		else
		{
			Assert(false, "recvBytes is ZERO.");
		}

		return static_cast<unsigned>(recvBytes);
	}

	unsigned __stdcall RecvPosFromClient(void* pArg)
	{
		// 6����Ʈ�� ����ȭ�� ��Ŷ�� �����մϴ�.
		// x            (2bytes) 
		// y            (2bytes)  
		// row          (1byte)	  
		// column       (1byte)

		static const size_t MAX_BYTES = 6;
		static InputMemoryStream istream(MAX_BYTES);
		Assert(istream.GetBufferPtr() != nullptr, "buffer need to memory allocation.");

		istream.ClearBuffer();
		int recvBytes = recv(gSocket, istream.GetBufferPtr(), MAX_BYTES, 0);
		if (recvBytes > 0)
		{
			auto pos = *(reinterpret_cast<std::shared_ptr<MyPoint>*>(pArg));

			istream.ReadFromBuffer(&(pos->X.first));  // x      (2bytes)
			istream.ReadFromBuffer(&(pos->Y.first));  // y      (2bytes)
			istream.ReadFromBuffer(&(pos->X.second)); // row    (1byte)
			istream.ReadFromBuffer(&(pos->Y.second)); // column (1byte)

			// ** PostMessage�� �����ϴ� ���� ���� �޶��� �� �־� ���X **
			SendMessage(ghWnd, MSG_DRAW_STONE, (WPARAM)&pos, NULL);
		}
		else
		{
			Assert(false, "recvBytes is ZERO.");
		}

		return static_cast<unsigned>(recvBytes);
	}
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
}
