#include "WindowPainter.h"

#include "Stationary.h"

// ==================================================================
// DeviceHandler
// ==================================================================

lycee::graphics::DeviceContextHandler::~DeviceContextHandler()
{
}

lycee::graphics::DeviceContextHandler::DeviceContextHandler(HDC hTargetDC)
	: hdc(hTargetDC)
{
}

HDC lycee::graphics::DeviceContextHandler::getHDC()
{
	return this->hdc;
}


lycee::graphics::WindowHandler::~WindowHandler()
{
	EndPaint(this->hWnd, &this->ps);
}

lycee::graphics::WindowHandler::WindowHandler(HWND hTargetWnd)
	: hWnd(hTargetWnd),
	hdc(NULL),
	ps({ 0 })
{
	hdc = BeginPaint(hWnd, &ps);
}

HDC lycee::graphics::WindowHandler::getHDC()
{
	return this->hdc;
}

// ==================================================================
// WindowPainter
// ==================================================================
lycee::graphics::WindowPainter::~WindowPainter()
{
	delete handler;
}

lycee::graphics::WindowPainter::WindowPainter(HWND hWnd)
	: handler(new lycee::graphics::WindowHandler(hWnd))
{
}

lycee::graphics::WindowPainter::WindowPainter(HDC hdc)
	: handler(new lycee::graphics::DeviceContextHandler(hdc))
{

}

// ==================================================================
// lines 

BOOL lycee::graphics::WindowPainter::line(const Pen &pen, long x1, long y1, long x2, long y2)
{
	POINT pts[2] = {
		{ x1, y1 },
		{ x2, y2 }
	};
	return this->polyline(pen, 2, pts);
}

BOOL lycee::graphics::WindowPainter::polyline(const Pen &pen, int cSize, const LPPOINT pts)
{
	return this->draw(
		pen,
		[&](HDC hdc) { return Polyline(hdc, pts, cSize); }
	);
}

BOOL lycee::graphics::WindowPainter::curve(const Pen &pen, int cSize, const LPPOINT pts)
{
	return this->draw(
		pen,
		[&](HDC hdc) { return PolyBezier(hdc, pts, cSize); }
	);
}
BOOL lycee::graphics::WindowPainter::draw(const Pen &pen, std::function<BOOL(HDC)> callback)
{
	return pen.draw(
		this->handler->getHDC(),
		callback
	);
}

// ==================================================================
// faces
BOOL lycee::graphics::WindowPainter::rectangle(
	const Brush &brush,
	const Pen &pen,
	const RECT &rect)
{
	return this->fill(brush, pen, [&](HDC hdc) {
		return Rectangle(hdc,
			rect.left, rect.top,
			rect.right, rect.bottom);
	});
}

BOOL lycee::graphics::WindowPainter::ellipse(
	const Brush &brush,
	const Pen &pen,
	const RECT &rect)
{
	return this->fill(brush, pen, [&](HDC hdc) {
		return Ellipse(hdc,
			rect.left, rect.top,
			rect.right, rect.bottom);
	});
}

BOOL lycee::graphics::WindowPainter::roundRect(
	const Brush &brush,
	const Pen &pen,
	const RECT &rect,
	const SIZE &roundSize)
{
	return this->fill(brush, pen, [&](HDC hdc) {
		return RoundRect(hdc,
			rect.left, rect.top,
			rect.right, rect.bottom,
			roundSize.cx, roundSize.cy);
	});
}

BOOL lycee::graphics::WindowPainter::fill(
	const Brush &brush,
	const Pen &pen,
	std::function<BOOL(HDC)> callback)
{
	return brush.draw(this->handler->getHDC(), [&](HDC hdc1) {
		return pen.draw(hdc1, callback);
	});
}

// ==================================================================
// text
BOOL lycee::graphics::WindowPainter::text(
	const Pencil &pencil,
	const Font &font,
	const lycee_string &text,
	const RECT &rect,
	UINT format)
{
	return pencil.draw(this->handler->getHDC(), [&](HDC hdc1) {
		return font.draw(hdc1, [&](HDC hdc2) {
			RECT r = rect;
			DrawText(hdc2, text.c_str(), -1, &r, format);
			return TRUE;
		});
	});
}

