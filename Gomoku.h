/*
	윈도우 및 게임 관련 헤더입니다.
*/

#pragma once
#pragma comment(linker, "/subsystem:windows")

#include <memory>

//#include "Network.h"
#include <Windows.h>
#include "Variables.h"

namespace gomokuGame
{
	typedef uint16_t						     coordinate_type;      // x or y 좌표 타입
	typedef uint8_t							     idx_type;		       // index 타입
	typedef std::pair<coordinate_type, idx_type> coordinate_with_idx;  // <x or y, index>
	
	struct MyPoint;
	struct InGameButtonInfo;
	struct InGamePPInfo;
	struct ImageInfo;
	class  PlayerInfo;

	/*------------------------------------
					윈도우 관련
	------------------------------------*/
	HWND CreateWnd(HINSTANCE hInstance, LPCWSTR wndClsName);
	INT	EnterMsgLoop();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	VOID CALLBACK MyTimeProc(HWND hWnd, UINT msg, UINT_PTR idTimer, DWORD dwTime);
	VOID OnPaint();


	/*------------------------------------
					게임 관련
	------------------------------------*/
	VOID InitGlobalVariables(HWND hWnd);

	VOID CreateStartMenu(HWND hWnd);
	VOID DeleteStartMenu();
	VOID CleanUp();


	bool IsValidPos(WORD x, WORD y, std::shared_ptr<MyPoint>* pOut);
	bool PutStone(const std::shared_ptr<MyPoint> pos);
	unsigned __stdcall SendPosToClient(void* pArg);
	unsigned __stdcall SendPosToServer(void* pArg);
	unsigned SendGameResult(bool bIsPlayer1Win, std::shared_ptr<MyPoint> pos = NULL);

	unsigned __stdcall RecvPosFromServer(void* pArg);
	unsigned __stdcall RecvPosFromClient(void* pArg);

	bool CheckWinCondition(char stone);
	bool CheckRight(idx_type row, idx_type col, char stone);
	bool CheckDown(idx_type row, idx_type col, char stone);
	bool CheckRightDown(idx_type row, idx_type col, char stone);
	bool CheckLeftDown(idx_type row, idx_type col, char stone);

	unsigned __stdcall CreateRoom(void* pArg);  /* 서버      */
	unsigned __stdcall JoinRoom(void* pArg);    /* 클라이언트 */

	HRESULT InitGameData(HWND hWnd);
	VOID InitCoordinate();
	VOID LoadGameScreen();

	VOID DrawMyImage(Gdiplus::Image* pImage, HDC hdc, float x, float y, float width, float height);
	VOID DrawPlayerPlace(HDC hdc, int x, int y, int width, int height);
	HWND DrawButton(int x, int y, int width, int height, HMENU buttonID, LPCWSTR buttonName);
	inline VOID DrawMyText(HDC hdc, long x, long y, long width, long height, const char* text);

	VOID SendPlayerInfo(SOCKET sock, std::shared_ptr<PlayerInfo> info);
	VOID RecvPlayerInfo(SOCKET sock, std::shared_ptr<PlayerInfo> info);
}
