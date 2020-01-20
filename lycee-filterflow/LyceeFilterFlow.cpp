#include "LyceeFilterFlow.h"

#include "resource.h"


lycee::LyceeFilterFlow::~LyceeFilterFlow()
{
}

lycee::LyceeFilterFlow::LyceeFilterFlow(HINSTANCE hInstance)
	: lycee::widgets::Application(hInstance),
	graph(),
	eventHandler(DefWindowProc),
	isDragging(false),
	ptStartMouse(),
	ptStartPanel(),
	draggingId(-1),
	popupMenu(NULL),
	ptBtnRight()
{
}

BOOL lycee::LyceeFilterFlow::start(const lycee_string &title, int width, int height, int nCmdShow)
{
	if (!this->initialize(
			TEXT("LYCEE-FILTERFLOW"),
			MAKEINTRESOURCE(ID_MAINMENU1),
			CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS
		)
	) {
		return FALSE;
	}
	
	setupEvent();
	entryEventHandler(&eventHandler);

	return this->run(title, width, height, nCmdShow);
}
