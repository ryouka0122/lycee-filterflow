#ifndef __LYCEE__WDIGETS__APPLICATION__HEADER__
#define __LYCEE__WDIGETS__APPLICATION__HEADER__

#include "../includes.h"


namespace lycee {

	namespace widgets {

		class EventHandler;

		class Application {
		// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
		// constructor/destructor
		// 
		public:
			virtual ~Application();
			explicit Application(HINSTANCE hInstance);

		// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
		// Application controller
		//
		public:

			BOOL initialize(LPCTSTR lpszClassName, LPCTSTR lpszMenuName, UINT style);

			BOOL run(const lycee_string &title, int width, int height, int nCmdShow);

			void release();

			HWND getHWND() {
				return this->hWnd;
			}

			HINSTANCE getHINSTANCE() {
				return this->hInstance;
			}

		private:
			ATOM atom;
			HINSTANCE hInstance;

			HWND hWnd;

			RECT adjustWindowRect(int width, int height, DWORD dwStyle, BOOL bMenu);


		// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
		// event dispatcher
		//
		public:
			void entryEventHandler(EventHandler *handler);

			virtual LRESULT dispatchEvent(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

		private:
			EventHandler *eventHandler;

		};

		// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
		// [MAIN EVENT CONTROLLER]
		//
		class MainEventController {
			friend class Application;

		private:
			~MainEventController();
			MainEventController();
			MainEventController(const MainEventController &);
			MainEventController& operator =(const MainEventController &);

			typedef std::map<HWND, Application*> application_map;
			typedef typename application_map::iterator map_iterator;

			static std::map<HWND, Application*> applicationList;
			static LRESULT CALLBACK GlobalWndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
		};

	}	// widgets

}	// lycee
#endif	// __LYCEE__WDIGETS__APPLICATION__HEADER__
