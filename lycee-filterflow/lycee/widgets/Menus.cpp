#include "Menus.h"


lycee::widgets::PopupMenu::~PopupMenu()
{
	DestroyMenu(hContextMenu);
}

lycee::widgets::PopupMenu::PopupMenu(HMENU hMenu)
	: hContextMenu(hMenu)
{
}

BOOL lycee::widgets::PopupMenu::show(HWND hWnd, const POINT &ptClient, UINT uFlags)
{
	POINT ptScreen = ptClient;
	ClientToScreen(hWnd, &ptScreen);
	return TrackPopupMenu(GetSubMenu(this->hContextMenu, 0), uFlags, ptScreen.x, ptScreen.y, 0, hWnd, NULL);
}

lycee::widgets::PopupMenu* lycee::widgets::PopupMenu::fromResource(
	HINSTANCE hInstance,
	int resourceId)
{
	return new lycee::widgets::PopupMenu(
		LoadMenu(hInstance, MAKEINTRESOURCE(resourceId))
		);
}
