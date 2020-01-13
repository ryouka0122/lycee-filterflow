#ifndef __LYCEE__IMAGE_PROCESSOR__HEADER__
#define __LYCEE__IMAGE_PROCESSOR__HEADER__

#include "..\includes.h"

#include "Image.h"


namespace lycee {
	
	namespace images {

		class ImageProcessor {
		public:
			typedef std::function<Image(const Image &)> process_functor;

			virtual ~ImageProcessor();
			explicit ImageProcessor(const lycee_string &name, process_functor processor);

			lycee_string name() {
				return this->__name;
			}

			Image invoke(Image srcimg);

		private:
			lycee_string __name;
			process_functor processor;

		public:
			static ImageProcessor* getDefault();

		};


	}	// images

}	// lycee
#endif	// __LYCEE__IMAGE_PROCESSOR__HEADER__
