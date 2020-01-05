#ifndef __LYCEE_APPLICATION__HEADER__
#define __LYCEE_APPLICATION__HEADER__

#include "includes.h"


namespace lycee {

	class Application {
	public:
		virtual ~Application();
		explicit Application(HINSTANCE hInstance);

		BOOL initialize();

		BOOL run(const lycee_string &title, int width, int height, int nCmdShow);

		void release();
		
		HWND getHWND() {
			return this->hWnd;
		}

	protected:
		virtual LRESULT dispatchEvent(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) = 0;

	private:
		ATOM atom;
		HINSTANCE hInstance;

		HWND hWnd;
		
		RECT adjustWindowRect(int width, int height, DWORD dwStyle, BOOL bMenu);

	private:
		typedef std::map<HWND, Application*> application_map;
		typedef typename application_map::iterator map_iterator;

		static std::map<HWND, Application*> applicationList;
		static LRESULT CALLBACK MainEventController(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
	};

}
#endif	// __LYCEE_APPLICATION__HEADER__
