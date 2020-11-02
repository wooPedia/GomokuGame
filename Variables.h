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


	/* GDI ���� ������ */
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	HDC gHdc;


	/* Direct3D ���� ������ */
	LPDIRECT3D9         gD3D        = nullptr;
	LPDIRECT3DDEVICE9   gD3D_Device = nullptr;
	LPD3DXSPRITE        gD3D_Sprite = nullptr;
	LPDIRECT3DTEXTURE9	gTexture   = nullptr;
	LPDIRECT3DTEXTURE9	gTexture2  = nullptr;


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

	std::queue<std::shared_ptr<InGameButtonInfo>> btnInfoQueue;
	std::queue<std::shared_ptr<InGamePPInfo>>     ppInfoQueue;
	std::queue<std::shared_ptr<ImageInfo>>        imageInfoQueue;
	std::queue<std::shared_ptr<TextInfo>>		  textInfoQueue;

	const wchar_t* gButtonNames[BT_COUNT] = { L"�� �����", L"���� �� ����", L"���� ����" }; // ���� �޴� ��ư �̸�
	
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


	/* ���� ���� ������ */
	static SOCKET gSocket;
	static std::shared_ptr<SignalManager> gReadyMngForSend;
	static std::shared_ptr<SignalManager> gReadyMngForRecv;
}

#endif // _VARIABLES_HEADER_
