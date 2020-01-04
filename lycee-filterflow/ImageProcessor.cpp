#include "ImageProcessor.h"
#include "Image.h"

lycee::ImageProcessor * lycee::ImageProcessor::getDefault()
{
	static ImageProcessor *silentProcessor = nullptr;
	if (silentProcessor == nullptr) {
		silentProcessor = new lycee::ImageProcessor([](lycee::Image img) -> lycee::Image {
			return img.clone();
		});
	}
	return silentProcessor;
}

lycee::ImageProcessor::~ImageProcessor()
{
}

lycee::ImageProcessor::ImageProcessor(std::function<lycee::Image(Image)> _processor)
	: processor(_processor)
{
}

lycee::Image lycee::ImageProcessor::run(Image srcimg)
{
	return this->processor(srcimg);
}



