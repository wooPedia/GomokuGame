#ifndef UNICODE
#define UNICODE
#endif // !UNICODE


<<<<<<< HEAD
=======
#include <d3d9.h>
#include <d3dx9.h>
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
#include <gdiplus.h>

#include <vector>
#include <queue>
#include <memory>

#include "EnumInfo.h"

#pragma comment(lib, "Gdiplus.lib")
<<<<<<< HEAD
=======
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

using namespace Gdiplus;

#ifndef _VARIABLES_HEADER_
#define _VARIABLES_HEADER_

namespace gomokuGame
{
	typedef uint16_t						     coordinate_type;      // x or y ��ǥ Ÿ��
	typedef uint8_t							     idx_type;		       // index Ÿ��
	typedef std::pair<coordinate_type, idx_type> coordinate_with_idx;  // <x or y, index>

	struct MyPoint;
	struct InGameButtonInfo;
	struct InGamePPInfo;
	struct ImageInfo;
	struct TextInfo;
	class  PlayerInfo;
	class  SignalManager;

	/* ������ ���� ������ */
	const wchar_t* wndTitleName = L"Gomoku Game";	/* ������ Ÿ��Ʋ */
	HWND ghWnd       = NULL;						/* ������ �ڵ� */
	HINSTANCE ghInst = NULL;					    /* �ν��Ͻ� �ڵ� */

	HWND gStartMenuBtns[3];
	HWND gReadyBtn = NULL;
	HWND gStartBtn = NULL;
	HWND gExitBtn  = NULL;

<<<<<<< HEAD
	HANDLE ghTimer = NULL;

	static const uint8_t BEGIN_TIME = 60 + 1;
	static uint8_t gTimeLimit = BEGIN_TIME;
	static RECT timeRT_P1 = { PI_P1_ID_X, PI_P_ID_Y + 50, PI_P_ID_WIDTH + PI_P1_ID_X, PI_P_ID_HEIGHT + 30 + PI_P_ID_Y + 50 };
	static RECT timeRT_P2 = { PI_P2_ID_X, PI_P_ID_Y + 50, PI_P_ID_WIDTH + PI_P2_ID_X, PI_P_ID_HEIGHT + 30 + PI_P_ID_Y + 50 };
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	/* GDI ���� ������ */
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	HDC gHdc;
<<<<<<< HEAD
	HDC gHdc_bStone;
	HDC gHdc_wStone;
=======


	/* Direct3D ���� ������ */
	LPDIRECT3D9         gD3D        = nullptr;
	LPDIRECT3DDEVICE9   gD3D_Device = nullptr;
	LPD3DXSPRITE        gD3D_Sprite = nullptr;
	LPDIRECT3DTEXTURE9	gTexture   = nullptr;
	LPDIRECT3DTEXTURE9	gTexture2  = nullptr;

>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	/* �ؽ��� ���� ��� */
	const wchar_t* IMG_GameBoard  = L"./Image/background.png";
	const wchar_t* IMG_BlackStone = L"./Image/blackstone.png";
	const wchar_t* IMG_WhiteStone = L"./Image/whitestone.png";
	const wchar_t* IMG_Player1    = L"./Image/player1.png";
	const wchar_t* IMG_Player2    = L"./Image/player2.png";


	/* ���� ���� ������ */
	std::unique_ptr<char[]>          board[BD_LENGTH]; //  2x2 �ٵ���, 'b': ������, 'w': �Ͼᵹ
	std::vector<coordinate_with_idx> xPos;			   //  <x, board �ε���>
	std::vector<coordinate_with_idx> yPos;		       //  <y, board �ε���>

	bool bReadyP1   = false;   // Player1 Ready ����
	bool bReadyP2   = false;   // Player2 Ready ����
	bool bBlackTurn = true;    // ������ ������ ��� true
	bool bServer    = false;   // ������ ��� true, Ŭ���̾�Ʈ�� ��� false
<<<<<<< HEAD
	bool bErase     = false;
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	std::queue<std::shared_ptr<InGameButtonInfo>> btnInfoQueue;
	std::queue<std::shared_ptr<InGamePPInfo>>     ppInfoQueue;
	std::queue<std::shared_ptr<ImageInfo>>        imageInfoQueue;
	std::queue<std::shared_ptr<TextInfo>>		  textInfoQueue;

	const wchar_t* gButtonNames[BT_COUNT] = { L"�� �����", L"���� �� ����", L"���� ����" }; // ���� �޴� ��ư �̸�
	
<<<<<<< HEAD
	static Image* gBlackStoneImgPtr;
	static Image* gWhiteStoneImgPtr;
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
	static Image* gBoardImgPtr;
	static Image* gPlayer1ImgPtr;
	static Image* gPlayer2ImgPtr;

	static eMode  gMode = eMode::MD_BEGIN_SCREEN;
	static ePhase gPhase;
<<<<<<< HEAD
	static bool bIsFirstEnter = true; // �� �ϸ��� �� ������ �����ϵ��� �մϴ�. 
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	static size_t gBlackStoneCount = 0;
	static size_t gWhiteStoneCount = 0;

	const char* PLAYER1_ID = "Player1";
	const char* PLAYER2_ID = "Player2";
	static std::shared_ptr<PlayerInfo> gPlayer1Ptr;
	static std::shared_ptr<PlayerInfo> gPlayer2Ptr;


	/* ���� ���� ������ */
	static SOCKET gSocket;
	static std::shared_ptr<SignalManager> gReadyMngForSend;
	static std::shared_ptr<SignalManager> gReadyMngForRecv;
}

#endif // _VARIABLES_HEADER_
