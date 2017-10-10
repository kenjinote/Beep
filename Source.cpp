#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

#define IDC_EDIT1 1000
#define IDC_EDIT2 2000

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit1;
	static HWND hEdit2;
	static HWND hButton;
	switch (msg)
	{
	case WM_CREATE:
		CreateWindow(TEXT("STATIC"), TEXT("周波数"), WS_VISIBLE | WS_CHILD | ES_NUMBER | ES_AUTOHSCROLL, 10, 10, 128, 32, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("1000"), WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_NUMBER | ES_AUTOHSCROLL, 138, 10, 256, 32, hWnd, (HMENU)IDC_EDIT1, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		CreateWindow(TEXT("STATIC"), TEXT("持続時間(ミリ秒)"), WS_VISIBLE | WS_CHILD | ES_NUMBER | ES_AUTOHSCROLL, 10, 50, 128, 32, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("1000"), WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_NUMBER | ES_AUTOHSCROLL, 138, 50, 256, 32, hWnd, (HMENU)IDC_EDIT2, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		hButton = CreateWindow(TEXT("BUTTON"), TEXT("ビープを鳴らす"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, 10, 90, 128, 32, hWnd, (HMENU)IDOK, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			const DWORD dwFreq = (DWORD)GetDlgItemInt(hWnd, IDC_EDIT1, 0, 0);
			const DWORD dwDuration = (DWORD)GetDlgItemInt(hWnd, IDC_EDIT2, 0, 0);
			Beep(dwFreq, dwDuration);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefDlgProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	TCHAR szClassName[] = TEXT("Window");
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		DLGWINDOWEXTRA,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("指定された周波数と長さでビープを鳴らす"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
