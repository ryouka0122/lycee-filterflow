#include "Application.h"

#include "resource.h"

lycee::Application::~Application()
{
	;
}

lycee::Application::Application(HINSTANCE hInstance)
	: atom(INVALID_ATOM),
	hInstance(hInstance),
	hWnd(NULL)
{
	;
}

BOOL lycee::Application::initialize()
{
	if (INVALID_ATOM != this->atom) {
		return FALSE;
	}

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(wcex);
	wcex.cbClsExtra = 0L;
	wcex.cbWndExtra = 0L;
	
	wcex.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;

	wcex.lpfnWndProc = MainEventController;
	wcex.lpszClassName = TEXT("LYCEE-FILTERFLOW");
	wcex.lpszMenuName = MAKEINTRESOURCE(ID_MAINMENU1);
	wcex.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

	this->atom = RegisterClassEx(&wcex);

	return trif(INVALID_ATOM != this->atom, TRUE, FALSE);

}

BOOL lycee::Application::run(const lycee_string &title, int width, int height, int nCmdShow)
{
	if (IsWindow(this->hWnd)) {
		return FALSE;
	}
	
	RECT rect = this->adjustWindowRect(width, height, WS_OVERLAPPEDWINDOW, TRUE);
	if (IsRectEmpty(&rect)) {
		return FALSE;
	}

	HWND wnd = CreateWindowEx(
		0L,
		MAKEINTATOM(this->atom),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, hInstance, this);

	if (!IsWindow(wnd)) {
		return FALSE;
	}
	this->hWnd = wnd;
	ShowWindow(this->hWnd, nCmdShow);
	UpdateWindow(this->hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return TRUE;
}

void lycee::Application::release()
{
	if (INVALID_ATOM == this->atom) {
		return;
	}
	UnregisterClass(MAKEINTATOM(this->atom), this->hInstance);
	this->atom = INVALID_ATOM;
}


RECT lycee::Application::adjustWindowRect(int width, int height, DWORD dwStyle, BOOL bMenu)
{
	RECT rcDesktop;
	if (width == 0 || height == 0 || !GetWindowRect(GetDesktopWindow(), &rcDesktop)) {
		return RECT{ 0, 0, 0, 0 };
	}

	RECT rcClient = { 0, 0, width, height };
	AdjustWindowRect(&rcClient, dwStyle, bMenu);

	LONG cWidth = rcClient.right - rcClient.left;
	LONG cHeight = rcClient.bottom - rcClient.top;
	
	LONG dWidth = rcDesktop.right - rcDesktop.left;
	LONG dHeight = rcDesktop.bottom - rcDesktop.top;
	return RECT {
		(dWidth - cWidth) / 2,
		(dHeight - cHeight) / 2,
		(dWidth - cWidth) / 2 + cWidth,
		(dHeight - cHeight) / 2 + cHeight,
	};
}
