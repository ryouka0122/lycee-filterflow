#include "WindowPainter.h"
#include "Stationary.h"


lycee::WindowPainter::~WindowPainter()
{
	EndPaint(hWnd, &ps);
}

lycee::WindowPainter::WindowPainter(HWND hWnd)
	: hWnd(hWnd),
	hPaintDC(nullptr),
	ps()
{
	hPaintDC = BeginPaint(hWnd, &ps);
}


// ==================================================================
// lines 

BOOL lycee::WindowPainter::line(const Pen &pen, long x1, long y1, long x2, long y2)
{
	POINT pts[2] = {
		{ x1, y1 },
		{ x2, y2 }
	};
	return this->polyline(pen, 2, pts);
}

BOOL lycee::WindowPainter::polyline(const Pen &pen, int cSize, const LPPOINT pts)
{
	return this->draw(
		pen,
		[&](HDC hdc) { return Polyline(hdc, pts, cSize); }
	);
}

BOOL lycee::WindowPainter::curve(const Pen &pen, int cSize, const LPPOINT pts)
{
	return this->draw(
		pen,
		[&](HDC hdc) { return PolyBezier(hdc, pts, cSize); }
	);
}
BOOL lycee::WindowPainter::draw(const Pen &pen, std::function<BOOL(HDC)> callback)
{
	return pen.draw(
		this->hPaintDC,
		callback
	);
}

// ==================================================================
// faces
BOOL lycee::WindowPainter::rectangle(
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

BOOL lycee::WindowPainter::ellipse(
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

BOOL lycee::WindowPainter::roundRect(
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

BOOL lycee::WindowPainter::fill(
	const Brush &brush,
	const Pen &pen,
	std::function<BOOL(HDC)> callback)
{
	return brush.draw(this->hPaintDC, [&](HDC hdc1) {
		return pen.draw(hdc1, callback);
	});
}

// ==================================================================
// text
BOOL lycee::WindowPainter::text(
	const Pencil &pencil,
	const Font &font,
	const lycee_string &text,
	const RECT &rect,
	UINT format)
{
	return pencil.draw(this->hPaintDC, [&](HDC hdc1) {
		return font.draw(hdc1, [&](HDC hdc2) {
			RECT r = rect;
			DrawText(hdc2, text.c_str(), -1, &r, format);
			return TRUE;
		});
	});
}

