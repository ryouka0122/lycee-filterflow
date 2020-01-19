#include "LyceeFilterFlow.h"

#include "resource.h"


lycee::LyceeFilterFlow::~LyceeFilterFlow()
{
}

lycee::LyceeFilterFlow::LyceeFilterFlow(HINSTANCE hInstance)
	: lycee::widgets::Application(hInstance),
	input(NULL),
	output(NULL),
	filterList(),
	eventHandler(DefWindowProc)
{
}

BOOL lycee::LyceeFilterFlow::start(const lycee_string &title, int width, int height, int nCmdShow)
{
	if (!this->initialize(
			TEXT("LYCEE-FILTERFLOW"),
			MAKEINTRESOURCE(ID_MAINMENU1),
			CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS
		)
	) {
		return FALSE;
	}
	
	setupEvent();
	entryEventHandler(&eventHandler);

	return this->run(title, width, height, nCmdShow);
}

BOOL lycee::LyceeFilterFlow::renderEdge(lycee::graphics::WindowPainter *painter)
{
	lycee::graphics::Pen edge(lycee::filtergraph::PanelProfile::LINE_BASECOLOR, 1);
	lycee::graphics::Pen line(lycee::filtergraph::PanelProfile::LINE_BASECOLOR, 1);
	lycee::graphics::SolidBrush faceBegin(lycee::filtergraph::PanelProfile::LINE_BEGIN_FACECOLOR);
	lycee::graphics::SolidBrush faceEnd(lycee::filtergraph::PanelProfile::LINE_END_FACECOLOR);

	for (auto iter = jointList.begin(); iter != jointList.end(); iter++) {
		std::optional<POINT> ptBegin = iter->first->getJointPt(filtergraph::JointType::OUTPUT);
		std::optional<POINT >ptEnd = iter->second->getJointPt(filtergraph::JointType::INPUT);
		if (!ptBegin || !ptEnd) continue;

		POINT begin = ptBegin.value(), end = ptEnd.value();

		POINT ptList[4] = {
			begin,
			POINT{ end.x, begin.y },
			POINT{ begin.x, end.y },
			end
		};
		painter->curve(line , 4, ptList);

		std::function<RECT(POINT, int)> circleRect = [&](POINT pt, int r) {
			return RECT{ pt.x - r, pt.y - r, pt.x + r, pt.y + r };
		};

		painter->ellipse(faceBegin, edge, circleRect(begin, lycee::filtergraph::PanelProfile::LINE_JOINT_RADIUS));
		painter->ellipse(faceEnd, edge, circleRect(end, lycee::filtergraph::PanelProfile::LINE_JOINT_RADIUS));
	}

	return TRUE;
}
