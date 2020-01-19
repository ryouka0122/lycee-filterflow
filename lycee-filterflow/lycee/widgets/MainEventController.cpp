#include "Application.h"


lycee::widgets::MainEventController::~MainEventController()
{
}

lycee::widgets::MainEventController::MainEventController()
{
}

lycee::widgets::MainEventController::MainEventController(const MainEventController &)
{
}

lycee::widgets::MainEventController& lycee::widgets::MainEventController::operator =(const MainEventController &)
{
	return *this;
}


std::map<HWND, lycee::widgets::Application*> lycee::widgets::MainEventController::applicationList;

LRESULT CALLBACK lycee::widgets::MainEventController::GlobalWndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
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
	}

	return lRes;
}
