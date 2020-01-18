#ifndef __LYCEE_FILTERFLOW__HEADER__
#define __LYCEE_FILTERFLOW__HEADER__

#include "lycee.h"

#include "filtergraph.h"


namespace lycee {

	class LyceeFilterFlow : virtual public widgets::Application {
	public:
		virtual ~LyceeFilterFlow();
		explicit LyceeFilterFlow(HINSTANCE hInstance);

		BOOL start(const lycee_string &title, int width, int height, int nCmdShow);


	protected:
		virtual LRESULT dispatchEvent(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

		virtual LRESULT doCreate(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
		virtual LRESULT doDestroy(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
		virtual LRESULT doPaint(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
		
		virtual LRESULT doCommand(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

		virtual LRESULT doLButtonDown(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
		virtual LRESULT doMouseMove(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
		virtual LRESULT doLButtonUp(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);


	private:
		std::deque<lycee::filtergraph::PanelViewFactory*> factories;
		
		lycee::filtergraph::PanelView *input;
		lycee::filtergraph::PanelView *output;

		std::deque<lycee::filtergraph::PanelView*> filterList;

		bool isDragging;
		POINT ptStartMouse;
		POINT ptStartPanel;
		lycee::filtergraph::PanelView *dragging;

		typedef std::pair<lycee::filtergraph::PanelView*, lycee::filtergraph::PanelView*> JointFlow;
		std::list<JointFlow> jointList;

		BOOL renderEdge(lycee::graphics::WindowPainter *painter);

	private:
		lycee::widgets::FileSelectDialog fileSelectDialog;

		void openDialog();
		void saveDialog();

	};

}	// lycee
#endif	// __LYCEE_FILTERFLOW__HEADER__
