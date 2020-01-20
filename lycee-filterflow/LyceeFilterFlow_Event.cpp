#include "LyceeFilterFlow.h"

#include "resource.h"

void lycee::LyceeFilterFlow::setupEvent()
{
#define CALL_EVENT(e) [&](lycee::widgets::EventInfo i) {return e(i); }

	this->eventHandler.entryEvent(WM_DESTROY, CALL_EVENT(this->doDestroy));
	this->eventHandler.entryEvent(WM_CLOSE, CALL_EVENT(this->doClose));

	this->eventHandler.entryEvent(WM_CREATE, CALL_EVENT(this->doCreate));
	this->eventHandler.entryEvent(WM_PAINT, CALL_EVENT(this->doPaint));

	this->eventHandler.entryEvent(WM_COMMAND, CALL_EVENT(this->doCommand));

	this->eventHandler.entryEvent(WM_MOUSEMOVE, CALL_EVENT(this->doMouseMove));
	this->eventHandler.entryEvent(WM_LBUTTONDOWN, CALL_EVENT(this->doLButtonDown));
	this->eventHandler.entryEvent(WM_LBUTTONUP, CALL_EVENT(this->doLButtonUp));
	this->eventHandler.entryEvent(WM_RBUTTONDOWN, CALL_EVENT(this->doRButtonDown));

#undef CALL_EVENT
}

LRESULT lycee::LyceeFilterFlow::doClose(lycee::widgets::EventInfo info)
{
	if (IDOK != lycee::widgets::MessageDialog::confirm(info.hWnd, TEXT("終了しますか？"))) {
		return 0L;
	}
	return info.callDefault();
}

LRESULT lycee::LyceeFilterFlow::doDestroy(lycee::widgets::EventInfo info)
{
	delete popupMenu;
	info.quit();
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doCreate(lycee::widgets::EventInfo info)
{
	fileSelectDialog
		.title(TEXT("ファイルを選んで"))
		.filter(TEXT("txt"), TEXT("Text File"))
		.filter(TEXT("bmp"), TEXT("Bitmap File"))
		.filter(TEXT("png"), TEXT("PNG File"))
		.filter(TEXT("jpg"), TEXT("JPEG File"))
		.filter(TEXT("gif"), TEXT("GIF Image"))
		.filter(TEXT("*"), TEXT("All Files"));

	popupMenu = lycee::widgets::PopupMenu::fromResource(this->getHINSTANCE(), IDR_MENU1);

	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doPaint(lycee::widgets::EventInfo info)
{
	lycee::graphics::WindowPainter painter(info.hWnd);
	graph.render(&painter);
	return 0L;
}

void lycee::LyceeFilterFlow::openDialog()
{
	if (auto result = fileSelectDialog.showLoadDialog(getHWND())) {
		lycee::widgets::MessageDialog::info(getHWND(), result.value());
	}
}

void lycee::LyceeFilterFlow::saveDialog()
{
	if (auto result = fileSelectDialog.showSaveDialog(getHWND())) {
		lycee::widgets::MessageDialog::info(getHWND(), result.value());
	}
}

LRESULT lycee::LyceeFilterFlow::doCommand(lycee::widgets::EventInfo info)
{
	lycee_string msg;

	switch (LOWORD(info.wParam)) {
	case ID_FILE_NEW:
		msg = TEXT("[File]>[NEW]");
		break;
	case ID_FILE_OPEN:
		openDialog();
		return 0L;
	case ID_FILE_SAVE:
		msg = TEXT("[File]>[SAVE]");
		break;
	case ID_FILE_SAVE_AS:
		saveDialog();
		return 0L;
	case ID_FILE_QUIT:
		info.send(WM_CLOSE);
		return 0L;

	case ID_ADDPANEL_FILTER:
		graph.addFilter(ptBtnRight.x, ptBtnRight.y);
		info.invalidate(TRUE);
		return 0L;
	case ID_ADDPANEL_INPUT:
		graph.addInput(ptBtnRight.x, ptBtnRight.y);
		info.invalidate(TRUE);
		break;
	case ID_ADDPANEL_OUTPUT:
		graph.addOutput(ptBtnRight.x, ptBtnRight.y);
		info.invalidate(TRUE);
		break;
	case ID__DELETEPANEL:
		graph.removePanelView(targetDeleteId);
		targetDeleteId = -1;
		info.invalidate(TRUE);
		break;

	}

	if (!msg.empty()) {
		lycee::widgets::MessageDialog::info(info.hWnd, msg);
	}
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doLButtonDown(lycee::widgets::EventInfo info)
{
	long x = LOWORD(info.lParam);
	long y = HIWORD(info.lParam);

	this->draggingId = graph.hittest(x, y);
	if (this->isDragging = (this->draggingId != -1)) {
		this->ptStartMouse.x = x;
		this->ptStartMouse.y = y;
		this->ptStartPanel = graph[this->draggingId]->getPosition();
	}
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doMouseMove(lycee::widgets::EventInfo info)
{
	if (!this->isDragging) {
		return 0L;
	}

	long x = LOWORD(info.lParam);
	long y = HIWORD(info.lParam);

	long dx = x - this->ptStartMouse.x;
	long dy = y - this->ptStartMouse.y;

	long newX = this->ptStartPanel.x + dx;
	long newY = this->ptStartPanel.y + dy;

	graph[this->draggingId]->moveTo(newX, newY);

	info.invalidate(true);
	
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doLButtonUp(lycee::widgets::EventInfo info)
{
	this->draggingId = -1;
	this->isDragging = false;

	return 0L;
}