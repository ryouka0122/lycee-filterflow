#include "Panels.h"

#include "Image.h"
#include "ImageProcessor.h"



// ============================================================================================
// Filter
// ============================================================================================
lycee::Filter::~Filter()
{
}

lycee::Filter::Filter()
	: processor(lycee::ImageProcessor::getDefault()),
	area({ 0 })
{
	SetRect(&area, 50, 50, 200, 180);
}

lycee::Filter::Filter(lycee::ImageProcessor *processor)
{
}

bool lycee::Filter::hittest(int x, int y)
{
	return area.left <= x && x < area.right 
		&& area.top <= y && y < area.bottom;
}

bool lycee::Filter::draw(lycee::WindowPainter *painter)
{
	return true;
}

lycee::Panel* lycee::Filter::copy()
{
	return nullptr;
}

lycee::Image lycee::Filter::process(const lycee::Image &srcimg)
{
	return this->processor->run(srcimg);
}

// ============================================================================================
// Transform
// ============================================================================================