#include "ImageProcessor.h"

#include "Image.h"


lycee::images::ImageProcessor * lycee::images::ImageProcessor::getDefault()
{
	static ImageProcessor *silentProcessor = nullptr;
	if (silentProcessor == nullptr) {
		silentProcessor = new lycee::images::ImageProcessor(
			TEXT("nameless"),
			[](const lycee::images::Image &img) {
				return img.clone();
			}
		);
	}
	return silentProcessor;
}

lycee::images::ImageProcessor::~ImageProcessor()
{
}

lycee::images::ImageProcessor::ImageProcessor(const lycee_string &name, lycee::images::ImageProcessor::process_functor _processor)
	: __name(name),
	processor(_processor)
{
}

lycee::images::Image lycee::images::ImageProcessor::invoke(lycee::images::Image srcimg)
{
	return this->processor(srcimg);
}



