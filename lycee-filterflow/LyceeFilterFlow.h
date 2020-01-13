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
		lycee::Panel *input;
		lycee::Panel *output;

		std::deque<lycee::Panel*> filterList;

		bool isDragging;
		POINT ptStartMouse;
		POINT ptStartPanel;
		lycee::Panel *dragging;

		typedef std::pair<lycee::Panel*, lycee::Panel*> JointFlow;
		std::list<JointFlow> jointList;

		BOOL renderEdge(lycee::gdis::WindowPainter *painter);

	private:
		lycee::widgets::FileSelectDialog fileSelectDialog;

		void openDialog();
		void saveDialog();

	};

}	// lycee
#endif	// __LYCEE_FILTERFLOW__HEADER__
