#include "LyceeFilterFlow.h"

#include "resource.h"

#include "Panels.h"
#include "ImageProcessor.h"
#include "WindowPainter.h"
#include "Stationary.h"


lycee::LyceeFilterFlow::~LyceeFilterFlow()
{
}

lycee::LyceeFilterFlow::LyceeFilterFlow(HINSTANCE hInstance)
	: lycee::Application(hInstance)
{
}

BOOL lycee::LyceeFilterFlow::start(const lycee_string &title, int width, int height, int nCmdShow)
{
	if (!this->initialize()) {
		return FALSE;
	}
	return this->run(title, width, height, nCmdShow);
}

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
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}

LRESULT lycee::LyceeFilterFlow::doDestroy(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	delete input;
	delete filter1;
	delete filter2;
	delete filter3;
	delete output;
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doCreate(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	input = lycee::Panel::newInput(POINT{ 100, 100 }, lycee::ImageProcessor::getDefault());
	output = lycee::Panel::newOutput(POINT{ 550, 300 }, lycee::ImageProcessor::getDefault());
	filter1 = lycee::Panel::newFilter(POINT{ 350, 100 }, lycee::ImageProcessor::getDefault());
	filter2 = lycee::Panel::newFilter(POINT{ 700, 100 }, lycee::ImageProcessor::getDefault());
	filter3 = lycee::Panel::newFilter(POINT{ 300, 300 }, lycee::ImageProcessor::getDefault());
	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doPaint(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	lycee::WindowPainter painter(hWnd);
	
	input->render(&painter);
	filter1->render(&painter);
	filter2->render(&painter);
	filter3->render(&painter);
	output->render(&painter);

	return 0L;
}

LRESULT lycee::LyceeFilterFlow::doCommand(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	lycee_string msg;

	switch (LOWORD(wp)) {
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
		MessageBox(hWnd, msg.c_str(), TEXT("Šm”F"), MB_OK);
	}
	return 0L;
}

