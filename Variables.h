#ifndef UNICODE
#define UNICODE
#endif // !UNICODE


#include <d3d9.h>
#include <d3dx9.h>
#include <gdiplus.h>

#include <vector>
#include <queue>
#include <memory>

#include "EnumInfo.h"

#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace Gdiplus;

#ifndef _VARIABLES_HEADER_
#define _VARIABLES_HEADER_

namespace gomokuGame
{
	typedef uint16_t						     coordinate_type;      // x or y 좌표 타입
	typedef uint8_t							     idx_type;		       // index 타입
	typedef std::pair<coordinate_type, idx_type> coordinate_with_idx;  // <x or y, index>

	struct MyPoint;
	struct InGameButtonInfo;
	struct InGamePPInfo;
	struct ImageInfo;
	struct TextInfo;
	class  PlayerInfo;
	class  SignalManager;

	/* 윈도우 관련 데이터 */
	const wchar_t* wndTitleName = L"Gomoku Game";	/* 윈도우 타이틀 */
	HWND ghWnd       = NULL;						/* 윈도우 핸들 */
	HINSTANCE ghInst = NULL;					    /* 인스턴스 핸들 */

	HWND gStartMenuBtns[3];
	HWND gReadyBtn = NULL;
	HWND gStartBtn = NULL;
	HWND gExitBtn  = NULL;


	/* GDI 관련 데이터 */
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	HDC gHdc;


	/* Direct3D 관련 데이터 */
	LPDIRECT3D9         gD3D        = nullptr;
	LPDIRECT3DDEVICE9   gD3D_Device = nullptr;
	LPD3DXSPRITE        gD3D_Sprite = nullptr;
	LPDIRECT3DTEXTURE9	gTexture   = nullptr;
	LPDIRECT3DTEXTURE9	gTexture2  = nullptr;


	/* 텍스쳐 파일 경로 */
	const wchar_t* IMG_GameBoard  = L"./Image/background.png";
	const wchar_t* IMG_BlackStone = L"./Image/blackstone.png";
	const wchar_t* IMG_WhiteStone = L"./Image/whitestone.png";
	const wchar_t* IMG_Player1    = L"./Image/player1.png";
	const wchar_t* IMG_Player2    = L"./Image/player2.png";


	/* 게임 관련 데이터 */
	std::unique_ptr<char[]>          board[BD_LENGTH]; //  2x2 바둑판, 'b': 검정돌, 'w': 하얀돌
	std::vector<coordinate_with_idx> xPos;			   //  <x, board 인덱스>
	std::vector<coordinate_with_idx> yPos;		       //  <y, board 인덱스>

	bool bReadyP1   = false;   // Player1 Ready 여부
	bool bReadyP2   = false;   // Player2 Ready 여부
	bool bBlackTurn = true;    // 검은돌 차례일 경우 true
	bool bServer    = false;   // 서버일 경우 true, 클라이언트일 경우 false

	std::queue<std::shared_ptr<InGameButtonInfo>> btnInfoQueue;
	std::queue<std::shared_ptr<InGamePPInfo>>     ppInfoQueue;
	std::queue<std::shared_ptr<ImageInfo>>        imageInfoQueue;
	std::queue<std::shared_ptr<TextInfo>>		  textInfoQueue;

	const wchar_t* gButtonNames[BT_COUNT] = { L"방 만들기", L"랜덤 방 입장", L"게임 종료" }; // 시작 메뉴 버튼 이름
	
	static Image* gBoardImgPtr;
	static Image* gPlayer1ImgPtr;
	static Image* gPlayer2ImgPtr;

	static eMode  gMode = eMode::MD_BEGIN_SCREEN;
	static ePhase gPhase;

	static size_t gBlackStoneCount = 0;
	static size_t gWhiteStoneCount = 0;

	const char* PLAYER1_ID = "Player1";
	const char* PLAYER2_ID = "Player2";
	static std::shared_ptr<PlayerInfo> gPlayer1Ptr;
	static std::shared_ptr<PlayerInfo> gPlayer2Ptr;


	/* 소켓 관련 데이터 */
	static SOCKET gSocket;
	static std::shared_ptr<SignalManager> gReadyMngForSend;
	static std::shared_ptr<SignalManager> gReadyMngForRecv;
}

#endif // _VARIABLES_HEADER_
