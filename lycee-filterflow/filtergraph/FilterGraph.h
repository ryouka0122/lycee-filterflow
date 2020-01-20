#ifndef __LYCEE__FILTERGRAPH__HEADER__
#define __LYCEE__FILTERGRAPH__HEADER__

#include "..\lycee.h"

#include "Panels.h"
#include "PanelViewFactory.h"


namespace lycee {

	namespace filtergraph {


		struct Connector {
			int fromId;
			int toId;
		};


		class FilterGraph {
		public:
			virtual ~FilterGraph();
			FilterGraph();

		public:
			void addInput(int x, int y)
			{
				add(x, y, inputFactory);
			}

			void addOutput(int x, int y)
			{
				add(x, y, outputFactory);
			}

			void addFilter(int x, int y)
			{
				add(x, y, filterFactory);
			}

			void removePanelView(int id);

			void removeAllPanelView();

			void connect(int from, int to);
			void disconnect(int from, int to);
			bool canConnect(int from, int to);

			void render(lycee::graphics::WindowPainter* painter);

			int hittest(int x, int y);

			int hittest(const POINT &pt)
			{
				return hittest(pt.x, pt.y);
			}

			PanelView* operator [](int index)
			{
				return panelViewList[index];
			}

		private:
			PanelViewFactory *inputFactory;
			PanelViewFactory *outputFactory;
			PanelViewFactory *filterFactory;

			std::deque<PanelView*> panelViewList;
			std::deque<Connector> connectorList;

			void add(int x, int y, PanelViewFactory* factory);

			void renderPanel(lycee::graphics::WindowPainter* painter);
			void renderConnector(lycee::graphics::WindowPainter* painter);

		};

	}	// filtergraph

}	// lycee
#endif	// __LYCEE__FILTERGRAPH__HEADER__
