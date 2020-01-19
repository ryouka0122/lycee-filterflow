#include "EventHandlers.h"

// ================================================================================
// EventHandler class
// ================================================================================

lycee::widgets::EventHandler::~EventHandler() { }


// ================================================================================
// CommonEventHandler class
// ================================================================================

lycee::widgets::CommonEventHandler::~CommonEventHandler()
{
}

lycee::widgets::CommonEventHandler::CommonEventHandler(default_callback _default)
	: defaultCallback(_default),
	eventList()
{
}

std::optional<LRESULT> lycee::widgets::CommonEventHandler::dispatch(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	std::optional<LRESULT> result;
	auto iter = this->eventList.find(uMsg);
	if (iter != this->eventList.end()) {
		EventInfo info = createEventInfo(hWnd, uMsg, wp, lp);
		if (hookBeforeInvoke(&info)) {
			result = iter->second(info);
		}
		hookAfterInvoke(&info);
	}
	else {
		result = this->defaultCallback(hWnd, uMsg, wp, lp);
	}
	return result;
}

void lycee::widgets::CommonEventHandler::entryEvent(UINT id, std::function<LRESULT(EventInfo)> callback)
{
	this->eventList[id] = callback;
}

void lycee::widgets::CommonEventHandler::clear()
{
	this->eventList.clear();
}

void lycee::widgets::CommonEventHandler::remove(UINT id)
{
	this->eventList.erase(id);
}

bool lycee::widgets::CommonEventHandler::hasId(UINT id)
{
	return (this->eventList.find(id) != this->eventList.end());
}

lycee::widgets::EventInfo lycee::widgets::CommonEventHandler::createEventInfo(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	lycee::widgets::EventInfo info;
	info.hWnd = hWnd;
	info.uMsg = uMsg;
	info.wParam = wp;
	info.lParam = lp;
	return info;
}

bool lycee::widgets::CommonEventHandler::hookBeforeInvoke(EventInfo *info)
{
	return true;
}

void lycee::widgets::CommonEventHandler::hookAfterInvoke(EventInfo *info)
{
	return;
}