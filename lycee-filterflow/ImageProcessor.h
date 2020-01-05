#ifndef __LYCEE__IMAGE_PROCESSOR__HEADER__
#define __LYCEE__IMAGE_PROCESSOR__HEADER__

#include "includes.h"


namespace lycee {
	
	class Image;

	class ImageProcessor {
	public:
		typedef std::function<lycee::Image(const lycee::Image &)> process_functor;

		virtual ~ImageProcessor();
		explicit ImageProcessor(const lycee_string &name, process_functor processor);

		lycee_string name() {
			return this->__name;
		}

		Image run(Image srcimg);

	private:
		lycee_string __name;
		process_functor processor;

	public:
		static ImageProcessor* getDefault();

	};

}	// lycee
#endif	// __LYCEE__IMAGE_PROCESSOR__HEADER__
