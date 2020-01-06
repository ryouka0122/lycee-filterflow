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
	: lycee::Application(hInstance),
	input(NULL),
	output(NULL),
	filter1(NULL),
	filter2(NULL),
	filter3(NULL),
	filter4(NULL)
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

	jointList.push_back(std::make_pair(input, filter1));
	jointList.push_back(std::make_pair(filter1, filter2));
	jointList.push_back(std::make_pair(input, filter3));
	jointList.push_back(std::make_pair(filter3, output));

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
	
	renderEdge(&painter);
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

BOOL lycee::LyceeFilterFlow::renderEdge(lycee::WindowPainter *painter)
{
	lycee::Pen edge(lycee::PanelProfile::LINE_BASECOLOR, 1);
	lycee::Pen line(lycee::PanelProfile::LINE_BASECOLOR, 2);
	lycee::SolidBrush faceBegin(lycee::PanelProfile::LINE_BEGIN_FACECOLOR);
	lycee::SolidBrush faceEnd(lycee::PanelProfile::LINE_END_FACECOLOR);

	for (auto iter = jointList.begin(); iter != jointList.end(); iter++) {
		POINT ptBegin, ptEnd;
		bool drawable = 
			iter->first->getJointPt(Panel::JointType::OUTPUT, &ptBegin)
				&& iter->second->getJointPt(Panel::JointType::INPUT, &ptEnd);
		if (!drawable) continue;

		POINT ptList[4] = {
			ptBegin,
			POINT{ ptEnd.x, ptBegin.y },
			POINT{ ptBegin.x, ptEnd.y },
			ptEnd
		};
		painter->curve(line , 4, ptList);

		std::function<RECT(POINT, int)> circleRect = [&](POINT pt, int r) {
			return RECT{ pt.x - r, pt.y - r, pt.x + r, pt.y + r };
		};

		painter->ellipse(faceBegin, edge, circleRect(ptBegin, PanelProfile::LINE_JOINT_RADIUS));
		painter->ellipse(faceEnd, edge, circleRect(ptEnd, PanelProfile::LINE_JOINT_RADIUS));
	}

	return TRUE;
}
