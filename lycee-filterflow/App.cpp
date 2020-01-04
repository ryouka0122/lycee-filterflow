#include "App.h"
#include "resource.h"

#include "Panels.h"
#include "Image.h"
#include "ImageProcessor.h"
#include "WindowPainter.h"

#include "Stationary.h"



bool dispatchMenuEvent(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	lycee_string msg;

	switch(LOWORD(wParam)) {
	case ID_FILE_NEW:
		msg = TEXT("[File]>[NEW]");
		break;
	case ID_FILE_OPEN:
		msg = TEXT("[File]>[OPEN]");
		break;
	case ID_FILE_QUIT:
		msg = TEXT("[File]>[QUIT]");
		break;
	}

	if (!msg.empty()) {
		MessageBox(hWnd, msg.c_str(), TEXT("確認"), MB_OK);
		return true;
	}
	return false;
}

struct SimplePanel {
	// ** COLOR PALETTE ** //
	enum { BACKGROUND_COLOR = RGB(0xFF, 0xC0, 0xC0) };
	enum { EDGE_COLOR = RGB(0x90, 0x40, 0x00) };

	// ** PANEL PROFILE ** //
	enum { PANEL_WIDTH = 120 };

	// ** TITLE PROFILE ** //
	enum { TITLE_TEXT_SIZE = 15 };
	enum { TITLE_HEIGHT = 16 };
	enum { TITLE_TEXT_MARGIN = 20 };

	// ** CONTENT PROFILE ** //
	enum { CONTENT_TEXT_MARGIN = 5 };
	enum { CONTENT_TEXT_SIZE = 25 };
	enum { CONTENT_MIN_HEIGHT = 80 };


	lycee_string title;
	POINT pos;
	lycee_string name;

	void draw(lycee::WindowPainter &painter) {
		lycee::Pen edge(EDGE_COLOR, 1);
		lycee::SolidBrush background(BACKGROUND_COLOR);
		lycee::Pencil pencil(RGB(0xff,0x00,0x00));
		lycee::Font font(TITLE_TEXT_SIZE);
		
		// render Title
		RECT rcTitle = {
			pos.x,
			pos.y,
			pos.x + PANEL_WIDTH,
			pos.y + TITLE_HEIGHT
		};

		painter.rectangle(background, edge, rcTitle);
		painter.text(pencil, font, title, rcTitle, DT_CENTER);

		// render Content
		RECT rcContent = {
			rcTitle.left, 
			rcTitle.bottom,
			rcTitle.right,
			rcTitle.bottom + CONTENT_MIN_HEIGHT
		};
		painter.rectangle(background, edge, rcContent);
		InflateRect(&rcContent, -CONTENT_TEXT_MARGIN, -CONTENT_TEXT_MARGIN);
		painter.text(pencil, font, name, rcContent);
	}
};

void paintPanel(HWND hWnd) {
	lycee::WindowPainter painter(hWnd);
	SimplePanel panel = {
		TEXT("* FILTER *"),
		POINT{50, 50},
		TEXT("test サンプル")
	};
	panel.draw(painter);
}

void paintPanel1(HWND hWnd) {
	lycee::WindowPainter painter(hWnd);
	
	lycee::Pen pen(RGB(0xff, 0x00, 0x00));
	lycee::SolidBrush brush(RGB(0x00,0xff,0x00));
	painter.line(pen, 10, 50, 700, 50);

	RECT rect = { 100, 100, 200, 200 };
	painter.rectangle(brush, pen, rect);

	lycee::Pencil pencil(RGB(0x00,0x00,0xff));
	lycee::Font font(20, TEXT("Meiryo"));

	painter.text(pencil, font, TEXT("sample テスト"), rect, 0);

	POINT pts[4] = {
		{ 50, 50 },
		{ 150, 50 },
		{ 50, 150 },
		{ 150, 150 },
	};
	
	painter.curve(pen, 4, pts);

}


LRESULT CALLBACK MainEventController(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
	case WM_CREATE:
		return 0L;

	case WM_PAINT:
		paintPanel(hWnd);
		return 0L;

	case WM_COMMAND:
		if (dispatchMenuEvent(hWnd, wParam, lParam)) {
			return 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


ATOM registerAtom(HINSTANCE hInstance) {
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

	return RegisterClassEx(&wcex);
}

HWND buildWindow(ATOM atom, HINSTANCE hInstance) {
	return CreateWindowEx(
		0L, MAKEINTATOM(atom), TEXT("Lycee FilterFlow"),
		WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
		NULL, NULL, hInstance, NULL);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	ATOM atom = registerAtom(hInstance);

	if (INVALID_ATOM == atom) {
		return -1;
	}
	
	HWND hWnd = buildWindow(atom, hInstance);
	if (!IsWindow(hWnd)) {
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	BOOL bRes;

	while (true) {
		bRes = GetMessage(&msg, NULL, 0L, 0L);
		if (bRes <= 0) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(MAKEINTATOM(atom), hInstance);
	return 0;
}
