#include "resource.h"

#include "LyceeFilterFlow.h"


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	lycee::LyceeFilterFlow app(hInstance);

	if (!app.start(TEXT("Lycee FilterFlow"), 1280, 720, nCmdShow)) {
		return -1;
	}
	return 0;
}
