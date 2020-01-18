#include "LyceeFilterFlow.h"



LRESULT lycee::LyceeFilterFlow::doRButtonDown(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	popupMenu->show(hWnd, POINT{LOWORD(lp), HIWORD(lp)});
	return 0L;
}
