#define _VARIABLES_HEADER_

#include "Gomoku.h"

using namespace gomokuGame;


LPCWSTR gWndClsName = L"GomokuWindow";  /* ������ Ŭ���� �̸� */

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, INT)
{
	// �����츦 �����մϴ�.
	HWND hWnd;
	hWnd = CreateWnd(hInstance, gWndClsName);

	HANDLE msgHandle;
	uint32_t tID;

	// �޼��� ���� ������ ����
	EnterMsgLoop();
	
	return 0;
}
