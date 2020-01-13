#include "PanelViewFactory.h"

// =====================================================================================
// AbstractPanelViewFactory class
// =====================================================================================

lycee::filtergraph::AbstractPanelViewFactory::~AbstractPanelViewFactory()
{
	;
}

lycee::filtergraph::AbstractPanelViewFactory::AbstractPanelViewFactory(const lycee_string &nameTemplate)
	: index(1),
	strTemplate(nameTemplate)
{
	;
}

lycee_string lycee::filtergraph::AbstractPanelViewFactory::generateName()
{
	int curIndex = this->index++;
	TCHAR temp[100] = { 0 };
#if defined(UNICODE) || defined(_UNICODE)
	swprintf(temp, this->strTemplate.c_str(), curIndex);
#else
	sprintf(temp, this->strTemplate.c_str(), curIndex);
#endif
	return lycee_string(temp);
}


// =====================================================================================
// InputPanelViewFactory class
// =====================================================================================

lycee::filtergraph::InputPanelViewFactory::~InputPanelViewFactory()
{
	;
}

lycee::filtergraph::InputPanelViewFactory::InputPanelViewFactory()
	: lycee::filtergraph::AbstractPanelViewFactory(TEXT("Input_%03d"))
{
	;
}

lycee::filtergraph::PanelView *lycee::filtergraph::InputPanelViewFactory::create(
	const POINT &pos, lycee::images::ImageProcessor *processor)
{
	return new lycee::filtergraph::InputPanelView(
		generateName(),
		processor,
		pos,
		SIZE{ PanelProfile::PANEL_WIDTH, PanelProfile::PANEL_HEIGHT }	
	);
}

// =====================================================================================
// FilterPanelViewFactory class
// =====================================================================================

lycee::filtergraph::FilterPanelViewFactory::~FilterPanelViewFactory()
{
	;
}

lycee::filtergraph::FilterPanelViewFactory::FilterPanelViewFactory()
	: lycee::filtergraph::AbstractPanelViewFactory(TEXT("Filter_%03d"))
{
	;
}

lycee::filtergraph::PanelView *lycee::filtergraph::FilterPanelViewFactory::create(
	const POINT &pos, lycee::images::ImageProcessor *processor)
{
	return new lycee::filtergraph::FilterPanelView(
		generateName(),
		processor,
		pos,
		SIZE{ PanelProfile::PANEL_WIDTH, PanelProfile::PANEL_HEIGHT }
	);
}



// =====================================================================================
// OutputPanelViewFactory class
// =====================================================================================

lycee::filtergraph::OutputPanelViewFactory::~OutputPanelViewFactory()
{
	;
}

lycee::filtergraph::OutputPanelViewFactory::OutputPanelViewFactory()
	: lycee::filtergraph::AbstractPanelViewFactory(TEXT("Output_%03d"))
{
	;
}

lycee::filtergraph::PanelView *lycee::filtergraph::OutputPanelViewFactory::create(
	const POINT &pos, lycee::images::ImageProcessor *processor)
{
	return new lycee::filtergraph::OutputPanelView(
		generateName(),
		processor,
		pos,
		SIZE{ PanelProfile::PANEL_WIDTH, PanelProfile::PANEL_HEIGHT }
	);
}
