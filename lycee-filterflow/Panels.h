#ifndef __LYCEE__PANELS__HEADER__
#define __LYCEE__PANELS__HEADER__

#include "includes.h"

namespace lycee {

	// ----------------------------------
	// WindowPainter.h
	class WindowPainter;

	// ----------------------------------
	// ImageProcessor.h
	class ImageProcessor;

	// ----------------------------------
	// Image.h
	class Image;


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


	// =============================================================================
	// Panel class
	// =============================================================================
	class Panel {
	public:
		enum HITTEST_TYPE {
			NONE,
			BODY,
			JOINT,
		};

	private:
		// ** copy guard ** //
		Panel(const Panel &);
		Panel& operator =(const Panel &) {
			return *this;
		}

	public:
		virtual ~Panel();

		explicit Panel(
			const lycee_string &type,
			ImageProcessor *target,
			const POINT &pos,
			const SIZE &size,
			const bool input,
			const bool output
		);

		virtual HITTEST_TYPE hittest(long x, long y);

		virtual BOOL render(WindowPainter *painter);

		virtual Image process(const Image &srcimg);

		bool acceptInput() const {
			return this->accept[JointType::INPUT] && !this->accept[JointType::OUTPUT];
		}

		bool acceptOutput() const {
			return !this->accept[JointType::INPUT] && this->accept[JointType::OUTPUT];
		}

		bool acceptProcess() const {
			return this->accept[JointType::INPUT] && this->accept[JointType::OUTPUT];
		}

		enum JointType {
			INPUT = 0,
			OUTPUT = 1,
			JOINT_MAX = 2,
		};

		bool getJointPt(JointType type, LPPOINT lpJointPt) const;

		POINT getPosition() const {
			return ptPanel;
		}

		SIZE getSize() const {
			return szPanel;
		}

		void move(long dx, long dy) {
			moveTo(this->ptPanel.x + dx, this->ptPanel.y + dy);
		}

		void moveTo(long newX, long newY) {
			ptPanel.x = newX;
			ptPanel.y = newY;
			calcRenderRect();
		}

	private:
		lycee_string strType;
		lycee_string strName;
		ImageProcessor *processor;

		POINT ptPanel;
		SIZE szPanel;

		RECT rcPanel;
		RECT rcTitle;
		RECT rcContent;

		bool accept[JOINT_MAX];
		RECT rcJoint[JOINT_MAX];

		void calcRenderRect();

		void renderJoint(WindowPainter * painter);
		void renderPanel(WindowPainter * painter);

	public:
		static Panel* newFilter(const POINT &pos, ImageProcessor *processor)
		{
			return new lycee::Panel(
				TEXT("FILTER"),
				processor,
				pos,
				SIZE{ lycee::PanelProfile::PANEL_WIDTH, lycee::PanelProfile::PANEL_HEIGHT },
				true,
				true
			);
		}

		static Panel* newInput(const POINT &pos, ImageProcessor *inputProcessor)
		{
			return new lycee::Panel(
				TEXT("INPUT"),
				inputProcessor,
				pos,
				SIZE{ lycee::PanelProfile::PANEL_WIDTH, lycee::PanelProfile::PANEL_HEIGHT },
				false,
				true
			);
		}

		static Panel* newOutput(const POINT &pos, ImageProcessor *outputProcessor)
		{
			return new lycee::Panel(
				TEXT("OUTPUT"),
				outputProcessor,
				pos,
				SIZE{ lycee::PanelProfile::PANEL_WIDTH, lycee::PanelProfile::PANEL_HEIGHT },
				true,
				false
			);
		}

	};




}	// lycee
#endif	// __LYCEE__PANELS__HEADER__
