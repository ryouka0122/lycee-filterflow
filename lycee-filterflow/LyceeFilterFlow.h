#ifndef __LYCEE_FILTERFLOW__HEADER__
#define __LYCEE_FILTERFLOW__HEADER__

#include "lycee.h"

#include "filtergraph.h"


namespace lycee {

	class LyceeFilterFlow : virtual public widgets::Application {
	public:
		virtual ~LyceeFilterFlow();
		explicit LyceeFilterFlow(HINSTANCE hInstance);

		BOOL start(const lycee_string &title, int width, int height, int nCmdShow);

	// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	// dispatch event
	protected:
		virtual LRESULT doCreate(lycee::widgets::EventInfo info);
		virtual LRESULT doClose(lycee::widgets::EventInfo info);
		virtual LRESULT doDestroy(lycee::widgets::EventInfo info);
		virtual LRESULT doPaint(lycee::widgets::EventInfo info);
		
		virtual LRESULT doCommand(lycee::widgets::EventInfo info);

		virtual LRESULT doLButtonDown(lycee::widgets::EventInfo info);
		virtual LRESULT doMouseMove(lycee::widgets::EventInfo info);
		virtual LRESULT doLButtonUp(lycee::widgets::EventInfo info);

	private:
		lycee::widgets::CommonEventHandler eventHandler;

		void setupEvent();

	private:
		lycee::filtergraph::FilterGraph graph;

		bool isDragging;
		POINT ptStartMouse;
		POINT ptStartPanel;
		int draggingId;
		
	private:
		lycee::widgets::FileSelectDialog fileSelectDialog;

		void openDialog();
		void saveDialog();

	// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	// Context Menu Event
	public:
		virtual LRESULT doRButtonDown(lycee::widgets::EventInfo info);

	private:
		lycee::widgets::PopupMenu *popupMenu;
		POINT ptBtnRight;
		int targetDeleteId;

		void setupPopupMenu();


	};

}	// lycee
#endif	// __LYCEE_FILTERFLOW__HEADER__
