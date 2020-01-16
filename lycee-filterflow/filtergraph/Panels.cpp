#include "Panels.h"

// ============================================================================================
// Panel
// ============================================================================================
lycee::filtergraph::Panel::~Panel()
{
}

lycee::filtergraph::Panel::Panel(
	const lycee_string &type,
	lycee::images::ImageProcessor *target,
	const POINT &pos,
	const SIZE &size,
	bool input,
	bool output
)
	: strType(type),
	strName(target->name()),
	processor(target),
	ptPanel(pos),
	szPanel(size),
	accept()
{
	accept[INPUT] = input;
	accept[OUTPUT] = output;

	this->adjustRenderRect();
}

void lycee::filtergraph::Panel::adjustRenderRect()
{
	rcJoint[INPUT].left		= ptPanel.x - PanelProfile::JOINT_WIDTH;
	rcJoint[INPUT].top		= ptPanel.y + szPanel.cy / 2 - PanelProfile::JOINT_HEIGHT / 2;
	rcJoint[INPUT].right	= rcJoint[INPUT].left + PanelProfile::JOINT_WIDTH;
	rcJoint[INPUT].bottom	= rcJoint[INPUT].top + PanelProfile::JOINT_HEIGHT;

	rcJoint[OUTPUT].left	= ptPanel.x + szPanel.cx;
	rcJoint[OUTPUT].top		= ptPanel.y + szPanel.cy / 2 - PanelProfile::JOINT_HEIGHT / 2;
	rcJoint[OUTPUT].right	= rcJoint[OUTPUT].left + PanelProfile::JOINT_WIDTH;
	rcJoint[OUTPUT].bottom	= rcJoint[OUTPUT].top + PanelProfile::JOINT_HEIGHT;

	rcPanel = {
		ptPanel.x,
		ptPanel.y,
		ptPanel.x + szPanel.cx,
		ptPanel.y + szPanel.cy
	};

	rcTitle = {
		ptPanel.x,
		ptPanel.y,
		ptPanel.x + szPanel.cx,
		ptPanel.y + PanelProfile::TITLE_HEIGHT,
	};

	rcContent = {
		ptPanel.x,
		rcTitle.bottom,
		rcTitle.right,
		ptPanel.y + szPanel.cy,
	};
}


// ============================================================================================
// PanelView
// ============================================================================================
lycee::filtergraph::PanelView::~PanelView()
{
	delete this->panel;
}

lycee::filtergraph::PanelView::PanelView(Panel *target)
	: panel(target)
{
	;
}

lycee::filtergraph::HITTEST_TYPE lycee::filtergraph::PanelView::hittest(long x, long y)
{
	if (PtInRect(&this->panel->rcPanel, POINT{ x, y })) {
		return HITTEST_TYPE::BODY;
	}
	return lycee::filtergraph::HITTEST_TYPE::NONE;
}

void lycee::filtergraph::PanelView::render(lycee::graphics::WindowPainter *painter)
{
	this->renderJoint(painter);
	this->renderPanel(painter);
	return;
}

lycee::images::Image lycee::filtergraph::PanelView::process(const lycee::images::Image &srcimg)
{
	return this->panel->processor->invoke(srcimg);
}

bool lycee::filtergraph::PanelView::isAccept(JointType type) const
{
	return this->panel->accept[type];
}


void lycee::filtergraph::PanelView::renderJoint(lycee::graphics::WindowPainter * painter)
{
	lycee::graphics::SolidBrush face(PanelProfile::JOINT_COLOR_FACE);
	lycee::graphics::Pen edge(PanelProfile::JOINT_COLOR_EDGE);

	// -------------------------------------------------------------
	// render joint
	if (this->isAccept(JointType::INPUT)) {
		painter->rectangle(face, edge, this->panel->rcJoint[JointType::INPUT]);
	}
	if (this->isAccept(JointType::OUTPUT)) {
		painter->rectangle(face, edge, this->panel->rcJoint[JointType::OUTPUT]);
	}
}

void lycee::filtergraph::PanelView::renderPanel(lycee::graphics::WindowPainter * painter)
{
	lycee::graphics::Pen edgePen(PanelProfile::TEXT_COLOR, 1);
	lycee::graphics::SolidBrush faceBrush(PanelProfile::BACKGROUND_COLOR);
	lycee::graphics::Pencil textPencil(PanelProfile::TEXT_COLOR);
	lycee::graphics::Font textFont;

	// -------------------------------------------------------------
	// render title
	textFont
		.size(PanelProfile::TITLE_TEXT_SIZE)
		.bold(true);

	painter->rectangle(faceBrush, edgePen, this->panel->rcTitle);
	painter->text(textPencil, textFont, this->panel->strType, this->panel->rcTitle, DT_CENTER);

	// -------------------------------------------------------------
	// render content
	RECT rc = this->panel->rcContent;
	textFont
		.size(PanelProfile::CONTENT_TEXT_SIZE)
		.bold(false);

	painter->rectangle(faceBrush, edgePen, rc);

	InflateRect(&rc, -PanelProfile::CONTENT_TEXT_MARGIN, -PanelProfile::CONTENT_TEXT_MARGIN);
	
	// TODO: make function for polymorphism
	painter->text(textPencil, textFont, this->panel->strName, rc, 0L);

}

std::optional<POINT> lycee::filtergraph::PanelView::getJointPt(lycee::filtergraph::JointType type) const
{
	std::optional<POINT> result;
	if (this->isAccept(type)) {
		long y = this->panel->ptPanel.y + this->panel->szPanel.cy / 2;
		long x = this->panel->ptPanel.x;
		if (type == JointType::INPUT) {
			x -= PanelProfile::JOINT_WIDTH;
		}
		else {
			x += this->panel->szPanel.cx + PanelProfile::JOINT_WIDTH;
		}
		result = POINT{ x, y };

	}
	return result;
}

// ============================================================================================
// InputPanelView
// ============================================================================================
lycee::filtergraph::InputPanelView::~InputPanelView()
{
	;
}

lycee::filtergraph::InputPanelView::InputPanelView(
	const lycee_string &name,
	lycee::images::ImageProcessor *processor,
	const POINT &pos,
	const SIZE &size)
	: lycee::filtergraph::PanelView(
		new lycee::filtergraph::Panel(name, processor, pos, size, false, true)
	)
{
	;
}

// ============================================================================================
// FilterPanelView
// ============================================================================================
lycee::filtergraph::FilterPanelView::~FilterPanelView()
{
	;
}

lycee::filtergraph::FilterPanelView::FilterPanelView(
	const lycee_string &name,
	lycee::images::ImageProcessor *processor,
	const POINT &pos,
	const SIZE &size)
	: lycee::filtergraph::PanelView(
		new lycee::filtergraph::Panel(name, processor, pos, size, true, true)
	)
{
	;
}

// ============================================================================================
// OutputPanelView
// ============================================================================================
lycee::filtergraph::OutputPanelView::~OutputPanelView()
{
	;
}

lycee::filtergraph::OutputPanelView::OutputPanelView(
	const lycee_string &name,
	lycee::images::ImageProcessor *processor,
	const POINT &pos,
	const SIZE &size)
	: lycee::filtergraph::PanelView(
		new lycee::filtergraph::Panel(name, processor, pos, size, true, false)
	)
{
	;
}
