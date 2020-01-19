#include "FilterGraph.h"

#include "..\lycee.h"

lycee::filtergraph::FilterGraph::~FilterGraph()
{
	removeAllPanelView();
}

lycee::filtergraph::FilterGraph::FilterGraph()
	: panelViewList(),
	connectorList(),
	inputFactory(new lycee::filtergraph::InputPanelViewFactory()),
	outputFactory(new lycee::filtergraph::OutputPanelViewFactory()),
	filterFactory(new lycee::filtergraph::FilterPanelViewFactory())
{
}

void lycee::filtergraph::FilterGraph::add(int x, int y, PanelViewFactory *factory)
{
	PanelView *pv = factory->create(POINT{x, y}, lycee::images::ImageProcessor::getDefault());
	panelViewList.push_back(pv);
}

void lycee::filtergraph::FilterGraph::removePanelView(int id)
{
	// erase connectors
	auto iter = std::remove_if(connectorList.begin(), connectorList.end(), [&](Connector x) {
		return x.fromId==id || x.toId==id;
	});
	connectorList.erase(iter, connectorList.end());

	// erase panel
	auto pvIter = panelViewList.begin() + id;
	delete *pvIter;
	panelViewList.erase(pvIter);
}

void lycee::filtergraph::FilterGraph::removeAllPanelView() 
{
	for (auto iter = panelViewList.begin(); iter != panelViewList.end(); iter++) {
		delete *iter;
	}
	panelViewList.clear();
	connectorList.clear();
}

void lycee::filtergraph::FilterGraph::connect(int from, int to)
{
	connectorList.push_back(Connector{ from, to });
}

void lycee::filtergraph::FilterGraph::disconnect(int from, int to)
{
	auto iter = std::find_if(connectorList.begin(), connectorList.end(), [&](Connector x) {
		return x.fromId == from && x.toId == to;
	});
	if (iter == connectorList.end()) {
		return;
	}
	connectorList.erase(iter);
}

bool lycee::filtergraph::FilterGraph::canConnect(int from, int to)
{
	auto iter = std::find_if(connectorList.begin(), connectorList.end(), [&](Connector x) {
		return x.fromId == from && x.toId == to;
	});
	return (iter != connectorList.end());
}

void lycee::filtergraph::FilterGraph::render(lycee::graphics::WindowPainter* painter)
{
	renderPanel(painter);
	renderConnector(painter);
}

int lycee::filtergraph::FilterGraph::hittest(int x, int y)
{
	for (int i = 0, l = (int)panelViewList.size(); i < l; i++) {
		if (HITTEST_TYPE::NONE != panelViewList[i]->hittest(x, y)) {
			return i;
		}
	}
	return -1;	// no hit anything.
}

void lycee::filtergraph::FilterGraph::renderPanel(lycee::graphics::WindowPainter* painter)
{
	for (auto iter = panelViewList.begin(); iter != panelViewList.end(); iter++) {
		(*iter)->render(painter);
	}
}

void lycee::filtergraph::FilterGraph::renderConnector(lycee::graphics::WindowPainter* painter)
{
	static std::function<RECT(POINT, int)> circleRect = [&](POINT pt, int r) {
		return RECT{ pt.x - r, pt.y - r, pt.x + r, pt.y + r };
	};

	lycee::graphics::Pen edge(lycee::filtergraph::PanelProfile::LINE_BASECOLOR, 1);
	lycee::graphics::Pen line(lycee::filtergraph::PanelProfile::LINE_BASECOLOR, 1);
	lycee::graphics::SolidBrush faceBegin(lycee::filtergraph::PanelProfile::LINE_BEGIN_FACECOLOR);
	lycee::graphics::SolidBrush faceEnd(lycee::filtergraph::PanelProfile::LINE_END_FACECOLOR);

	for (auto iter = connectorList.begin(); iter != connectorList.end(); iter++) {
		PanelView* from = panelViewList[iter->fromId];
		PanelView* to = panelViewList[iter->toId];
		
		std::optional<POINT> ptBegin = from->getJointPt(JointType::OUTPUT);
		if (!ptBegin) continue;
		
		std::optional<POINT> ptEnd = to->getJointPt(JointType::INPUT);
		if (!ptEnd) continue;

		POINT
			begin = ptBegin.value(),
			end = ptEnd.value(),
			ptList[4] = {
				begin,
				POINT{ end.x, begin.y },
				POINT{ begin.x, end.y },
				end
			};
		painter->curve(line, 4, ptList);

		painter->ellipse(faceBegin, edge, circleRect(begin, lycee::filtergraph::PanelProfile::LINE_JOINT_RADIUS));
		painter->ellipse(faceEnd, edge, circleRect(end, lycee::filtergraph::PanelProfile::LINE_JOINT_RADIUS));
	}
}
