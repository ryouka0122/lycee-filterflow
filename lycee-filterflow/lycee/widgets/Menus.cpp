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
	return TrackPopupMenu(GetSubMenu(hContextMenu, 0), uFlags, ptScreen.x, ptScreen.y, 0, hWnd, NULL);
}

lycee::widgets::PopupMenu& lycee::widgets::PopupMenu::state(UINT menuId, bool bState)
{
	MENUITEMINFO mii = { 0 };
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_STATE;
	GetMenuItemInfo(hContextMenu, menuId, FALSE, &mii);
	mii.fState = bState ? MFS_ENABLED : MFS_GRAYED;
	SetMenuItemInfo(hContextMenu, menuId, FALSE, &mii);
	return *this;
}

lycee::widgets::PopupMenu* lycee::widgets::PopupMenu::fromResource(
	HINSTANCE hInstance,
	int resourceId)
{
	return new lycee::widgets::PopupMenu(
		LoadMenu(hInstance, MAKEINTRESOURCE(resourceId))
		);
}
