#include "LyceeFilterFlow.h"

#include "resource.h"

LRESULT lycee::LyceeFilterFlow::doRButtonDown(lycee::widgets::EventInfo info)
{
	ptBtnRight = POINT{ LOWORD(info.lParam), HIWORD(info.lParam) };
	targetDeleteId = graph.hittest(ptBtnRight);
	setupPopupMenu();

	popupMenu->show(info.hWnd, ptBtnRight);
	return 0L;
}

void lycee::LyceeFilterFlow::setupPopupMenu()
{
	popupMenu->state(ID__DELETEPANEL, (targetDeleteId != -1));

}
