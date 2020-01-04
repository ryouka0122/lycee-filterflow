#ifndef __LYCEE__IMAGE_PROCESSOR__HEADER__
#define __LYCEE__IMAGE_PROCESSOR__HEADER__

#include "includes.h"


namespace lycee {
	
	class Image;

	class ImageProcessor {
	public:
		static ImageProcessor* getDefault();

		virtual ~ImageProcessor();
		explicit ImageProcessor(std::function<lycee::Image(Image)> processor);

		Image run(Image srcimg);

	private:
		std::function<lycee::Image(Image)> processor;
	};

}	// lycee
#endif	// __LYCEE__IMAGE_PROCESSOR__HEADER__
