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
	auto result = lycee::commons::Strings::printf(this->strTemplate, curIndex);
	return result ? result.value() : lycee_string();
}


// =====================================================================================
// InputPanelViewFactory class
// =====================================================================================

lycee::filtergraph::InputPanelViewFactory::~InputPanelViewFactory()
{
	;
}

lycee::filtergraph::InputPanelViewFactory::InputPanelViewFactory(const lycee_string &nameTemplate)
	: lycee::filtergraph::AbstractPanelViewFactory(nameTemplate)
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


lycee::filtergraph::FilterPanelViewFactory::FilterPanelViewFactory(const lycee_string &nameTemplate)
	: lycee::filtergraph::AbstractPanelViewFactory(nameTemplate)
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

lycee::filtergraph::OutputPanelViewFactory::OutputPanelViewFactory(const lycee_string &nameTemplate)
	: lycee::filtergraph::AbstractPanelViewFactory(nameTemplate)
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
