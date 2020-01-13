#ifndef __LYCEE__PANELVIEW_FACTORY__HEADER__
#define __LYCEE__PANELVIEW_FACTORY__HEADER__

#include "..\lycee.h"

#include "Panels.h"

namespace lycee {

	namespace filtergraph {

		class PanelViewFactory {
		public:
			virtual ~PanelViewFactory() = 0 { }

			virtual PanelView *create(const POINT &pos, lycee::images::ImageProcessor *processor) = 0;

		};

		class AbstractPanelViewFactory : virtual public PanelViewFactory {
		protected:
			virtual ~AbstractPanelViewFactory();
			explicit AbstractPanelViewFactory(const lycee_string &nameTemplate);

			virtual lycee_string generateName();

		private:
			int index;
			lycee_string strTemplate;
		};

		class InputPanelViewFactory : virtual public AbstractPanelViewFactory {
		public:
			virtual ~InputPanelViewFactory();
			InputPanelViewFactory();

			virtual PanelView *create(const POINT &pos, lycee::images::ImageProcessor *processor);

		};


		class FilterPanelViewFactory : virtual public AbstractPanelViewFactory {
		public:
			virtual ~FilterPanelViewFactory();
			FilterPanelViewFactory();

			virtual PanelView *create(const POINT &pos, lycee::images::ImageProcessor *processor);

		};


		class OutputPanelViewFactory : virtual public AbstractPanelViewFactory {
		public:
			virtual ~OutputPanelViewFactory();
			OutputPanelViewFactory();

			virtual PanelView *create(const POINT &pos, lycee::images::ImageProcessor *processor);

		};


	}	// filtergraph

}	// lycee
#endif	// __LYCEE__PANELVIEW_FACTORY__HEADER__
