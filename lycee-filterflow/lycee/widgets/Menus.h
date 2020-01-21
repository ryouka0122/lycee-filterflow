#ifndef __LYCEE__WIDGETS__MENUS__HEADER__
#define __LYCEE__WIDGETS__MENUS__HEADER__

#include "..\includes.h"


namespace lycee {

	namespace widgets {

		class PopupMenu {
		private:
			explicit PopupMenu(HMENU hMenu);

			PopupMenu(const PopupMenu &pm) { }
			PopupMenu& operator =(const PopupMenu &pm) {
				return *this;
			}

		public:
			virtual ~PopupMenu();
			
			BOOL show(HWND hWnd, const POINT &ptClient) {
				return show(hWnd, ptClient, TPM_LEFTALIGN);
			}
			
			BOOL show(HWND hWnd, const POINT &ptClient, UINT uFlags);

			PopupMenu& enable(UINT menuId)
			{
				return state(menuId, true);
			}

			PopupMenu& disable(UINT menuId)
			{
				return state(menuId, false);
			}
			
			PopupMenu& state(UINT menuId, bool bState);


		private:
			HMENU hContextMenu;
			
		public:
			static PopupMenu* fromResource(HINSTANCE hInstance, int resourceId);

		};


	}	// widgets

}	// lycee
#endif	// __LYCEE__WIDGETS__MENUS__HEADER__
