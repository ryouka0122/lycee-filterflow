#ifndef __LYCEE__WINDOW_PAINTER__HEADER__
#define __LYCEE__WINDOW_PAINTER__HEADER__

#include "includes.h"

namespace lycee {

	class Brush;
	class Pen;
	class Pencil;
	class Font;

	// ==================================================================
	// DeviceHandler
	// ==================================================================
	class DeviceHandler {
	public:
		virtual ~DeviceHandler() = 0 { }
		virtual HDC getHDC() = 0;
	};

	class DeviceContextHandler : virtual public DeviceHandler {
	public:
		virtual ~DeviceContextHandler();
		explicit DeviceContextHandler(HDC hTargetDC);

		virtual HDC getHDC();
	private:
		HDC hdc;
	};

	class WindowHandler : virtual public DeviceHandler {
	public:
		virtual ~WindowHandler();
		explicit WindowHandler(HWND hTargetWnd);

		virtual HDC getHDC();
	private:
		HWND hWnd;
		HDC hdc;
		PAINTSTRUCT ps;
	};


	// ==================================================================
	// WindowPainter
	// ==================================================================
	class WindowPainter {
	private:
		WindowPainter(const WindowPainter &other);
		WindowPainter& operator =(const WindowPainter &other) {
			return *this;
		}

	public:
		virtual ~WindowPainter();
		explicit WindowPainter(HWND hWnd);
		WindowPainter(HDC hdc);

		// ==================================================================
		// lines 
		BOOL line(const Pen &pen, long x1, long y1, long x2, long y2);
		BOOL polyline(const Pen &pen, int cSize, const LPPOINT pts);
		BOOL curve(const Pen &pen, int cSize, const LPPOINT pts);

		BOOL draw(const Pen &pen, std::function<BOOL(HDC)> callback);

		// ==================================================================
		// faces
		BOOL rectangle(const Brush &brush, const Pen &pen, const RECT &rect);
		BOOL ellipse(const Brush &brush, const Pen &pen, const RECT &rect);
		BOOL roundRect(const Brush &brush, const Pen &pen, const RECT &rect, const SIZE &roundSize);
		
		BOOL fill(const Brush &brush, const Pen &pen, std::function<BOOL(HDC)> callback);
		
		// ==================================================================
		// text
		BOOL text(const Pencil &pencil, const Font &font, const lycee_string &text, const RECT &rect, UINT format = 0L);

	private:
		DeviceHandler *handler;
	};
	
}	// lycee
#endif	// __LYCEE__WINDOW_PAINTER__HEADER__
