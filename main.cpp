#define _VARIABLES_HEADER_

#include "Gomoku.h"

#include <string>
using namespace gomokuGame;


LPCWSTR gWndClsName = L"GomokuWindow";  /* ������ Ŭ���� �̸� */

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	// �����츦 �����մϴ�.
	HWND hWnd;
	hWnd = CreateWnd(hInstance, gWndClsName);

	HANDLE msgHandle;

	// �޼��� ���� ������ ����
	EnterMsgLoop();
	
	return 0;
}
