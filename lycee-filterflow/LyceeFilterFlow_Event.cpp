#include "LyceeFilterFlow.h"

#include "resource.h"


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

	for (auto iter = factories.begin(); iter != factories.end(); iter++) {
		delete *iter;
	}
	factories.clear();
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doCreate(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	
	factories.push_back(new lycee::filtergraph::InputPanelViewFactory(TEXT("Input[%03d]")));
	factories.push_back(new lycee::filtergraph::OutputPanelViewFactory(TEXT("Output[%03d]")));
	factories.push_back(new lycee::filtergraph::FilterPanelViewFactory(TEXT("Filter[%03d]")));

	input = factories[0]->create(POINT{ 100, 100 }, lycee::images::ImageProcessor::getDefault());
	output = factories[1]->create(POINT{ 550, 300 }, lycee::images::ImageProcessor::getDefault());
	filterList.push_back(
		factories[2]->create(POINT{ 350, 100 }, lycee::images::ImageProcessor::getDefault()));
	filterList.push_back(
		factories[2]->create(POINT{ 700, 100 }, lycee::images::ImageProcessor::getDefault()));
	filterList.push_back(
		factories[2]->create(POINT{ 300, 300 }, lycee::images::ImageProcessor::getDefault()));

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
	lycee::gdis::WindowPainter painter(hWnd);

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
		lycee::widgets::MessageDialog::info(getHWND(), result.value());
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
		if(IDOK == lycee::widgets::MessageDialog::confirm(hWnd, TEXT("終了しますか？"))) {
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