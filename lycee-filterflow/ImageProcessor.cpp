#include "ImageProcessor.h"
#include "Image.h"

lycee::ImageProcessor * lycee::ImageProcessor::getDefault()
{
	static ImageProcessor *silentProcessor = nullptr;
	if (silentProcessor == nullptr) {
		silentProcessor = new lycee::ImageProcessor(
			TEXT("nameless"),
			[](const lycee::Image &img) {
				return img.clone();
			}
		);
	}
	return silentProcessor;
}

lycee::ImageProcessor::~ImageProcessor()
{
}

lycee::ImageProcessor::ImageProcessor(const lycee_string &name, lycee::ImageProcessor::process_functor _processor)
	: __name(name),
	processor(_processor)
{
}

lycee::Image lycee::ImageProcessor::run(Image srcimg)
{
	return this->processor(srcimg);
}



