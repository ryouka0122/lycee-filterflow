#include "FilterGraph.h"


lycee::filtergraph::FilterGraph::~FilterGraph()
{
}

lycee::filtergraph::FilterGraph::FilterGraph(HWND hTargetWnd)
	: hWnd(hTargetWnd),
	panelList(),
	edgeList()
{
}

void lycee::filtergraph::FilterGraph::insertPanel(Panel *panel)
{
	this->panelList.push_back(panel);
}

void lycee::filtergraph::FilterGraph::joinPanel(panel_size_type begin, panel_size_type end)
{
	this->edgeList.push_back(lycee::filtergraph::Edge{begin, end});
}

void lycee::filtergraph::FilterGraph::render(HDC hdc)
{
	lycee::graphics::WindowPainter painter(hdc);

	for (auto iter = this->panelList.begin(); iter != this->panelList.end(); iter++) {
		renderPanel(&painter, *iter);
	}

	for (auto iter = this->edgeList.begin(); iter != this->edgeList.end(); iter++) {
		renderEdge(&painter, &(*iter));
	}

}

void lycee::filtergraph::FilterGraph::renderPanel(lycee::graphics::WindowPainter* painter, Panel *panel)
{

}

void lycee::filtergraph::FilterGraph::renderEdge(lycee::graphics::WindowPainter* painter, Edge *edge)
{
	;
}
