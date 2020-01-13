#ifndef __LYCEE__FILTERGRAPH__HEADER__
#define __LYCEE__FILTERGRAPH__HEADER__

#include "..\lycee.h"


namespace lycee {

	class Panel;
	
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

		void renderPanel(lycee::gdis::WindowPainter* painter, Panel *panel);

		void renderEdge(lycee::gdis::WindowPainter* painter, Edge *edge);

	};



}	// lycee
#endif	// __LYCEE__FILTERGRAPH__HEADER__
