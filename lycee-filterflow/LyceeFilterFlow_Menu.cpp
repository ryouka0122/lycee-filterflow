#include "LyceeFilterFlow.h"



LRESULT lycee::LyceeFilterFlow::doRButtonDown(lycee::widgets::EventInfo info)
{
	popupMenu->show(info.hWnd, POINT{LOWORD(info.lParam), HIWORD(info.lParam)});
	return 0L;
}
