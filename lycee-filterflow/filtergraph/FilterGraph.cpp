#include "FilterGraph.h"

#include "Panels.h"


lycee::FilterGraph::~FilterGraph()
{
}

lycee::FilterGraph::FilterGraph(HWND hTargetWnd)
	: hWnd(hTargetWnd),
	panelList(),
	edgeList()
{
}

void lycee::FilterGraph::insertPanel(Panel *panel)
{
	this->panelList.push_back(panel);
}

void lycee::FilterGraph::joinPanel(panel_size_type begin, panel_size_type end)
{
	this->edgeList.push_back(lycee::Edge{begin, end});
}

void lycee::FilterGraph::render(HDC hdc)
{
	lycee::gdis::WindowPainter painter(hdc);

	for (auto iter = this->panelList.begin(); iter != this->panelList.end(); iter++) {
		renderPanel(&painter, *iter);
	}

	for (auto iter = this->edgeList.begin(); iter != this->edgeList.end(); iter++) {
		renderEdge(&painter, &(*iter));
	}

}

void lycee::FilterGraph::renderPanel(lycee::gdis::WindowPainter* painter, Panel *panel)
{

}

void lycee::FilterGraph::renderEdge(lycee::gdis::WindowPainter* painter, Edge *edge)
{
	;
}
