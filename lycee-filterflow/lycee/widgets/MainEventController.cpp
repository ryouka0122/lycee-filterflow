#include "Application.h"


std::map<HWND, lycee::widgets::Application*> lycee::widgets::Application::applicationList;

LRESULT CALLBACK lycee::widgets::Application::MainEventController(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	if (uMsg == WM_CREATE) {
		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lp;
		lycee::widgets::Application *targetApplication = (lycee::widgets::Application*)lpcs->lpCreateParams;
		applicationList.emplace(hWnd, targetApplication);
		return targetApplication->dispatchEvent(hWnd, uMsg, wp, lp);
	}

	map_iterator iter = applicationList.find(hWnd);
	if (iter == applicationList.end()) {
		return DefWindowProc(hWnd, uMsg, wp, lp);
	}

	lycee::widgets::Application *app = iter->second;
	LRESULT lRes = app->dispatchEvent(hWnd, uMsg, wp, lp);

	if (uMsg == WM_DESTROY) {
		applicationList.erase(iter);
		if (applicationList.size() == 0) {
			PostQuitMessage(0);
		}
	}

	return lRes;
}
