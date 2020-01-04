#ifndef __LYCEE__PANELS__HEADER__
#define __LYCEE__PANELS__HEADER__

#include "includes.h"

namespace lycee {

	// ----------------------------------
	// WindowPainter.h
	class WindowPainter;

	// ----------------------------------
	// ImageProcessor.h
	class ImageProcessor;

	// ----------------------------------
	// Image.h
	class Image;


	// ----------------------------------
	// Panel interface
	class Panel {
	private:
		// ** copy guard ** //
		Panel(const Panel &);
		Panel& operator =(const Panel &) {
			return *this;
		}

	protected:
		virtual ~Panel() = 0 { }
		Panel() { }

	public:
		virtual bool hittest(int x, int y) = 0;
		virtual bool draw(WindowPainter *painter) = 0;
		virtual Panel* copy() = 0;

		virtual Image process(const Image &srcimg) = 0;

	private:
		lycee_string title;
		;
	};

	// ----------------------------------
	// Image Filter class
	class Filter : virtual public Panel {
	public:
		virtual ~Filter();
		Filter();
		Filter(ImageProcessor *processor);

		virtual bool hittest(int x, int y);
		virtual bool draw(WindowPainter *painter);
		virtual Panel* copy();

		virtual Image process(const Image &srcimg);

	private:
		ImageProcessor *processor;
		RECT area;

	};

	// ----------------------------------
	// Image Transform class


}	// lycee
#endif	// __LYCEE__PANELS__HEADER__
