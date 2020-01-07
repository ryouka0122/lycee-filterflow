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
	filterList()
{
}

BOOL lycee::LyceeFilterFlow::start(const lycee_string &title, int width, int height, int nCmdShow)
{
	if (!this->initialize()) {
		return FALSE;
	}
	return this->run(title, width, height, nCmdShow);
}

BOOL lycee::LyceeFilterFlow::renderEdge(lycee::WindowPainter *painter)
{
	lycee::Pen edge(lycee::PanelProfile::LINE_BASECOLOR, 1);
	lycee::Pen line(lycee::PanelProfile::LINE_BASECOLOR, 1);
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
