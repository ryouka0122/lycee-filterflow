#ifndef __LYCEE_FILTERFLOW__HEADER__
#define __LYCEE_FILTERFLOW__HEADER__

#include "includes.h"

#include "Application.h"
#include "Panels.h"

namespace lycee {

	class LyceeFilterFlow : virtual public Application {
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

	private:
		lycee::Panel *input;
		lycee::Panel *output;

		lycee::Panel *filter1;
		lycee::Panel *filter2;
		lycee::Panel *filter3;
		lycee::Panel *filter4;

		typedef std::pair<lycee::Panel*, lycee::Panel*> JointFlow;
		std::list<JointFlow> jointList;


		BOOL renderEdge(lycee::WindowPainter *painter);
	};

}	// lycee
#endif	// __LYCEE_FILTERFLOW__HEADER__
