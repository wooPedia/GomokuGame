#define _VARIABLES_HEADER_

#include "Gomoku.h"

<<<<<<< HEAD
#include <string>
=======
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e
using namespace gomokuGame;


LPCWSTR gWndClsName = L"GomokuWindow";  /* ������ Ŭ���� �̸� */

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	// �����츦 �����մϴ�.
	HWND hWnd;
	hWnd = CreateWnd(hInstance, gWndClsName);

	HANDLE msgHandle;
<<<<<<< HEAD
=======
	uint32_t tID;
>>>>>>> 983b2590c9a49ad9c1561202d61873c1c10c6c7e

	// �޼��� ���� ������ ����
	EnterMsgLoop();
	
	return 0;
}
