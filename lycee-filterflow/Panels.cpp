#include "Panels.h"

#include "Image.h"
#include "ImageProcessor.h"
#include "Stationary.h"
#include "WindowPainter.h"

// ============================================================================================
// Panel
// ============================================================================================
lycee::Panel::~Panel()
{
}

lycee::Panel::Panel(
	const lycee_string &type,
	ImageProcessor *target,
	const POINT &pos,
	const SIZE &size,
	const bool input,
	const bool output
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

	this->calcRenderRect();
}

void lycee::Panel::calcRenderRect()
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
		ptPanel.y + lycee::PanelProfile::TITLE_HEIGHT,
	};

	rcContent = {
		ptPanel.x,
		rcTitle.bottom,
		rcTitle.right,
		ptPanel.y + szPanel.cy,
	};
}

lycee::Panel::HITTEST_TYPE lycee::Panel::hittest(int x, int y)
{
	return lycee::Panel::HITTEST_TYPE::NONE;
}

BOOL lycee::Panel::render(WindowPainter *painter)
{
	this->renderJoint(painter);
	this->renderPanel(painter);
	return TRUE;
}

lycee::Image lycee::Panel::process(const lycee::Image &srcimg)
{
	return this->processor->run(srcimg);
}

void lycee::Panel::renderJoint(WindowPainter * painter)
{
	// -------------------------------------------------------------
	// render joint
	for (int i = 0; i < JointType::JOINT_MAX; i++) {
		if (this->accept[i]) {
			painter->rectangle(
				lycee::SolidBrush(PanelProfile::JOINT_COLOR_FACE),
				lycee::Pen(PanelProfile::JOINT_COLOR_EDGE),
				rcJoint[i]
			);
		}
	}
}

void lycee::Panel::renderPanel(WindowPainter * painter)
{
	lycee::Pen edgePen(PanelProfile::TEXT_COLOR, 1);
	lycee::SolidBrush faceBrush(PanelProfile::BACKGROUND_COLOR);
	lycee::Pencil textPencil(PanelProfile::TEXT_COLOR);
	lycee::Font textFont;

	// -------------------------------------------------------------
	// render title
	textFont
		.size(PanelProfile::TITLE_TEXT_SIZE)
		.bold(true);

	painter->rectangle(faceBrush, edgePen, rcTitle);
	painter->text(textPencil, textFont, this->strType, rcTitle, DT_CENTER);

	// -------------------------------------------------------------
	// render content
	RECT rc = rcContent;
	textFont
		.size(PanelProfile::CONTENT_TEXT_SIZE)
		.bold(false);

	painter->rectangle(faceBrush, edgePen, rc);

	InflateRect(&rc, -PanelProfile::CONTENT_TEXT_MARGIN, -PanelProfile::CONTENT_TEXT_MARGIN);
	painter->text(textPencil, textFont, this->strName, rc, 0L);

}

bool lycee::Panel::getJointPt(JointType type, LPPOINT lpJointPt) const
{
	if ( !(type==JointType::INPUT || type==JointType::OUTPUT)
		|| !this->accept[type]
		) {
		return false;
	}
	long y = ptPanel.y + szPanel.cy / 2;
	long x = ptPanel.x;
	if (type==JointType::INPUT) {
		x -= PanelProfile::JOINT_WIDTH;
	}
	else {
		x += szPanel.cx + PanelProfile::JOINT_WIDTH;
	}
	lpJointPt->x = x;
	lpJointPt->y = y;
	return true;
}
