#ifndef __LYCEE__PANELS__HEADER__
#define __LYCEE__PANELS__HEADER__

#include "..\lycee.h"


namespace lycee {

	namespace filtergraph {

		// ----------------------------------
		// Panel Profile
		struct PanelProfile {
			// ** COLOR PALETTE ** //
			enum { BACKGROUND_COLOR = RGB(0xFF, 0xC0, 0xC0) };
			enum { EDGE_COLOR = RGB(0x90, 0x40, 0x00) };
			enum { TEXT_COLOR = RGB(0xFF, 0x50, 0x50) };

			// ** PANEL PROFILE ** //
			enum { PANEL_WIDTH = 120 };
			enum { PANEL_HEIGHT = 100 };

			// ** JOINT PROFILE ** //
			enum { JOINT_WIDTH = 10 };
			enum { JOINT_HEIGHT = 20 };
			enum { JOINT_COLOR_FACE = RGB(0x90, 0x90, 0x90) };
			enum { JOINT_COLOR_EDGE = RGB(0x50, 0x50, 0x50) };

			// ** TITLE PROFILE ** //
			enum { TITLE_TEXT_SIZE = 15 };
			enum { TITLE_HEIGHT = 16 };
			enum { TITLE_TEXT_MARGIN = 20 };

			// ** CONTENT PROFILE ** //
			enum { CONTENT_TEXT_MARGIN = 5 };
			enum { CONTENT_TEXT_SIZE = 25 };
			enum { CONTENT_MIN_HEIGHT = 80 };

			// ** JOINT LINE PROFILE ** //
			enum { LINE_BASECOLOR = RGB(0x50, 0x50, 0x50) };
			enum { LINE_BEGIN_FACECOLOR = RGB(0xFF, 0xFF, 0xFF) };
			enum { LINE_END_FACECOLOR = RGB(0x00, 0x00, 0x00) };
			enum { LINE_JOINT_RADIUS = 3 };

		};

		enum HITTEST_TYPE {
			NONE,
			BODY,
			JOINT,
		};

		enum JointType {
			INPUT = 0,
			OUTPUT = 1,
			JOINT_MAX = 2,
		};


		// =============================================================================
		// Panel class
		// =============================================================================
		struct Panel {
			virtual ~Panel();

			explicit Panel(
				const lycee_string &type,
				lycee::images::ImageProcessor *target,
				const POINT &pos,
				const SIZE &size,
				bool input,
				bool output
			);

			lycee_string strType;
			lycee_string strName;
			lycee::images::ImageProcessor *processor;

			POINT ptPanel;
			SIZE szPanel;

			RECT rcPanel;
			RECT rcTitle;
			RECT rcContent;

			bool accept[JOINT_MAX];
			RECT rcJoint[JOINT_MAX];


			void adjustRenderRect();
		};


		// =============================================================================
		// PanelView class
		// =============================================================================
		class PanelView {
		private:
			// ** copy guard ** //
			PanelView(const PanelView &);
			PanelView& operator =(const PanelView &) {
				return *this;
			}

		public:
			virtual ~PanelView();

		protected:
			PanelView(Panel *target);

		public:
			virtual HITTEST_TYPE hittest(long x, long y);

			virtual lycee::images::Image process(const lycee::images::Image &srcimg);

			virtual bool isAccept(JointType type) const;

			std::optional<POINT> getJointPt(JointType type) const;

			POINT getPosition() const {
				return this->panel->ptPanel;
			}

			SIZE size() const {
				return this->panel->szPanel;
			}

			void move(long dx, long dy) {
				moveTo(this->panel->ptPanel.x + dx, this->panel->ptPanel.y + dy);
			}

			void moveTo(long newX, long newY) {
				this->panel->ptPanel.x = newX;
				this->panel->ptPanel.y = newY;
				this->panel->adjustRenderRect();
			}

			void render(lycee::graphics::WindowPainter *painter);

		private:
			Panel * panel;

			void renderJoint(lycee::graphics::WindowPainter * painter);
			void renderPanel(lycee::graphics::WindowPainter * painter);

		};

		class InputPanelView : virtual public PanelView {
		public:
			virtual ~InputPanelView();
			InputPanelView(
				const lycee_string &name,
				lycee::images::ImageProcessor *processor,
				const POINT &pos,
				const SIZE &size);
		};

		class FilterPanelView : virtual public PanelView {
		public:
			virtual ~FilterPanelView();
			FilterPanelView(
				const lycee_string &name,
				lycee::images::ImageProcessor *processor,
				const POINT &pos,
				const SIZE &size);
		};

		class OutputPanelView : virtual public PanelView {
		public:
			virtual ~OutputPanelView();
			OutputPanelView(
				const lycee_string &name,
				lycee::images::ImageProcessor *processor,
				const POINT &pos,
				const SIZE &size);
		};


	}	// filtergraph

}	// lycee
#endif	// __LYCEE__PANELS__HEADER__
