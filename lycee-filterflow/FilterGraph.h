#ifndef __LYCEE__FILTERGRAPH__HEADER__
#define __LYCEE__FILTERGRAPH__HEADER__

#include "includes.h"


namespace lycee {
	
	class Panel;
	class WindowPainter;

	struct Edge {
		typedef typename std::list<Panel*>::size_type size_type;

		size_type begin;
		size_type end;
	};


	class FilterGraph {
	public:
		typedef typename std::list<Panel*>::size_type panel_size_type;
		typedef typename std::list<Edge>::size_type edge_size_type;

		virtual ~FilterGraph();
		explicit FilterGraph(HWND hWnd);

	private:
		HWND hWnd;

	public:
		void insertPanel(Panel *panel);
		void joinPanel(panel_size_type begin, panel_size_type end);

		void render(HDC hdc);



	private:
		std::list<Panel*> panelList;
		std::list<Edge> edgeList;

		void renderPanel(WindowPainter* painter, Panel *panel);

		void renderEdge(WindowPainter* painter, Edge *edge);

	};



}	// lycee
#endif	// __LYCEE__FILTERGRAPH__HEADER__
