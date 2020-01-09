#include "LyceeFilterFlow.h"

#include "resource.h"
#include "ImageProcessor.h"
#include "WindowPainter.h"


LRESULT lycee::LyceeFilterFlow::dispatchEvent(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	switch (uMsg) {
	case WM_CREATE:
		return this->doCreate(hWnd, uMsg, wp, lp);
	case WM_PAINT:
		return this->doPaint(hWnd, uMsg, wp, lp);
	case WM_COMMAND:
		return this->doCommand(hWnd, uMsg, wp, lp);
	case WM_DESTROY:
		return this->doDestroy(hWnd, uMsg, wp, lp);
	case WM_MOUSEMOVE:
		return this->doMouseMove(hWnd, uMsg, wp, lp);
	case WM_LBUTTONDOWN:
		return this->doLButtonDown(hWnd, uMsg, wp, lp);
	case WM_LBUTTONUP:
		return this->doLButtonUp(hWnd, uMsg, wp, lp);
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}

LRESULT lycee::LyceeFilterFlow::doDestroy(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	delete input;
	for (auto iter = this->filterList.begin(); iter != this->filterList.end(); iter++) {
		delete *iter;
	}
	delete output;
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doCreate(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	input = lycee::Panel::newInput(POINT{ 100, 100 }, lycee::ImageProcessor::getDefault());
	output = lycee::Panel::newOutput(POINT{ 550, 300 }, lycee::ImageProcessor::getDefault());
	filterList.push_back(
		lycee::Panel::newFilter(POINT{ 350, 100 }, lycee::ImageProcessor::getDefault()));
	filterList.push_back(
		lycee::Panel::newFilter(POINT{ 700, 100 }, lycee::ImageProcessor::getDefault()));
	filterList.push_back(
		lycee::Panel::newFilter(POINT{ 300, 300 }, lycee::ImageProcessor::getDefault()));

	jointList.push_back(std::make_pair(input, filterList[0]));
	jointList.push_back(std::make_pair(filterList[0], filterList[1]));
	jointList.push_back(std::make_pair(input, filterList[2]));
	jointList.push_back(std::make_pair(filterList[2], output));

	fileSelectDialog
		.title(TEXT("ファイルを選んで"))
		.filter(TEXT("txt"), TEXT("Text File"))
		.filter(TEXT("bmp"), TEXT("Bitmap File"))
		.filter(TEXT("png"), TEXT("PNG File"))
		.filter(TEXT("jpg"), TEXT("JPEG File"))
		.filter(TEXT("gif"), TEXT("GIF Image"))
		.filter(TEXT("*"), TEXT("All Files"));
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doPaint(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	lycee::WindowPainter painter(hWnd);

	input->render(&painter);
	for (auto iter = this->filterList.begin(); iter != this->filterList.end(); iter++) {
		(*iter)->render(&painter);
	}
	output->render(&painter);

	renderEdge(&painter);
	return 0L;
}

void lycee::LyceeFilterFlow::openDialog()
{
	auto result = fileSelectDialog.showLoadDialog(getHWND());
	if (result) {
		MessageBox(getHWND(), result.value().c_str(), TEXT("RESULT"), MB_OK);
	}
}

void lycee::LyceeFilterFlow::saveDialog()
{
	if (auto result = fileSelectDialog.showSaveDialog(getHWND())) {
		MessageBox(getHWND(), result.value().c_str(), TEXT("RESULT"), MB_OK);
	}
}

LRESULT lycee::LyceeFilterFlow::doCommand(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	lycee_string msg;

	switch (LOWORD(wp)) {
	case ID_FILE_NEW:
		msg = TEXT("[File]>[NEW]");
		break;
	case ID_FILE_OPEN:
		openDialog();
		break;
	case ID_FILE_SAVE:
		msg = TEXT("[File]>[SAVE]");
		break;
	case ID_FILE_SAVE_AS:
		saveDialog();
		break;
	case ID_FILE_QUIT:
		if (IDOK == MessageBox(hWnd, TEXT("終了しますか？"), TEXT("確認"), MB_ICONQUESTION | MB_OKCANCEL)) {
			DestroyWindow(hWnd);
		}
		break;
	}

	if (!msg.empty()) {
		MessageBox(hWnd, msg.c_str(), TEXT("確認"), MB_OK);
	}
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doLButtonDown(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	long x = LOWORD(lp);
	long y = HIWORD(lp);
	
	this->dragging = NULL;
	this->isDragging = false;

	if (input->hittest(x, y)) {
		this->isDragging = true;
		this->dragging = input;
		this->ptStartMouse.x = x;
		this->ptStartMouse.y = y;
		this->ptStartPanel = input->getPosition();
	}
	else if (output->hittest(x, y)) {
		this->isDragging = true;
		this->dragging = output;
		this->ptStartMouse.x = x;
		this->ptStartMouse.y = y;
		this->ptStartPanel = output->getPosition();
	}
	else for (auto iter = filterList.begin(); iter != filterList.end(); iter++) {
		auto panel = *iter;
		if (panel->hittest(x, y)) {
			this->isDragging = true;
			this->dragging = panel;
			this->ptStartMouse.x = x;
			this->ptStartMouse.y = y;
			this->ptStartPanel = panel->getPosition();
			break;
		}
	}
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doMouseMove(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	if (!this->isDragging) {
		return 0L;
	}

	long x = LOWORD(lp);
	long y = HIWORD(lp);

	long dx = x - this->ptStartMouse.x;
	long dy = y - this->ptStartMouse.y;

	long newX = this->ptStartPanel.x + dx;
	long newY = this->ptStartPanel.y + dy;

	this->dragging->moveTo(newX, newY);

	InvalidateRect(hWnd, NULL, TRUE);

	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doLButtonUp(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	this->dragging = NULL;
	this->isDragging = false;

	return 0L;
}