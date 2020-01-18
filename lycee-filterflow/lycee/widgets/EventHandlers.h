#ifndef __LYCEE__WIDGETS__EVENT_HANDLER__HEADER__
#define __LYCEE__WIDGETS__EVENT_HANDLER__HEADER__

#include "..\includes.h"


namespace lycee {

	namespace widgets {

		struct EventInfo {
			HWND hWnd;
			UINT uMsg;
			WPARAM wParam;
			LPARAM lParam;

			virtual LRESULT dispatch() {
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		};


		// ====================================================================================
		// EventHandler class
		// ====================================================================================
		class EventHandler {
		public:
			virtual ~EventHandler() = 0;

			virtual std::optional<LRESULT> dispatch(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) = 0;
		};


		class CommonEventHandler : public virtual EventHandler {
		public:
			typedef std::function<LRESULT(EventInfo)> callback_type;
			
			virtual ~CommonEventHandler();

			CommonEventHandler();

			virtual std::optional<LRESULT> dispatch(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

			void entryEvent(UINT id, std::function<LRESULT(EventInfo)> callback);
			
			void clear();

			void remove(UINT id);

			bool hasId(UINT id);

		protected:
			virtual EventInfo createEventInfo(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);

			virtual bool hookBeforeInvoke(EventInfo *info);

			virtual void hookAfterInvoke(EventInfo *info);

		private:
			std::map<UINT, callback_type> eventList;

		};


	}	// widgets

}	// lycee
#endif	// __LYCEE__WIDGETS__EVENT_HANDLER__HEADER__
