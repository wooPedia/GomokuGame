#define _VARIABLES_HEADER_

#include "Gomoku.h"

#include <string>
using namespace gomokuGame;


LPCWSTR gWndClsName = L"GomokuWindow";  /* 윈도우 클래스 이름 */

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	// 윈도우를 생성합니다.
	HWND hWnd;
	hWnd = CreateWnd(hInstance, gWndClsName);

	HANDLE msgHandle;

	// 메세지 루프 스레드 시작
	EnterMsgLoop();
	
	return 0;
}
