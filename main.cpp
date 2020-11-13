#define _VARIABLES_HEADER_

#include "Gomoku.h"

<<<<<<< HEAD
<<<<<<< HEAD
#include <string>
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
using namespace gomokuGame;


LPCWSTR gWndClsName = L"GomokuWindow";  /* 윈도우 클래스 이름 */

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	// 윈도우를 생성합니다.
	HWND hWnd;
	hWnd = CreateWnd(hInstance, gWndClsName);

	HANDLE msgHandle;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	uint32_t tID;
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
=======
	uint32_t tID;
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	// 메세지 루프 스레드 시작
	EnterMsgLoop();
	
	return 0;
}
