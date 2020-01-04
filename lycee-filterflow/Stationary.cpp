#include "Stationary.h"

// ====================================================================================
// Pen
// ====================================================================================
lycee::Pen::~Pen()
{
}

lycee::Pen::Pen()
	: Pen(RGB(0,0,0), 1, PS_SOLID)
{
}

lycee::Pen::Pen(COLORREF crColor)
	: Pen(crColor, 1, PS_SOLID)
{
}

lycee::Pen::Pen(COLORREF crColor, int cWidth)
	: Pen(crColor, cWidth, PS_SOLID)
{
}

lycee::Pen::Pen(COLORREF crColor, int cWidth, int iStyle)
	: color(crColor),
	width(cWidth),
	style(iStyle)
{
}

lycee::Pen::Pen(const Pen &_Other)
	: color(_Other.color),
	width(_Other.width),
	style(_Other.style)
{
}

lycee::Pen& lycee::Pen::operator =(const Pen& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
		this->width = _Other.width;
		this->style = _Other.style;
	}
	return *this;
}

BOOL lycee::Pen::draw(HDC hdc, lycee::Pen::gui_callback callback) const
{
	HPEN hPen = CreatePen(this->style, this->width, this->color);
	if (hPen == NULL) {
		return FALSE;
	}
	HPEN hOldPen = SelectPen(hdc, hPen);

	BOOL res = callback(hdc);

	SelectPen(hdc, hOldPen);
	DeletePen(hPen);
	return res;
}

// ====================================================================================
// Brush
// ====================================================================================

BOOL lycee::Brush::draw(HDC hdc, lycee::SolidBrush::gui_callback callback) const
{
	HBRUSH hBrush = this->create();
	if (hBrush == NULL) {
		return FALSE;
	}

	HBRUSH hOldBrush = SelectBrush(hdc, hBrush);

	BOOL res = callback(hdc);

	SelectBrush(hdc, hOldBrush);
	DeleteBrush(hBrush);
	return res;
}

lycee::SolidBrush::~SolidBrush()
{
}

lycee::SolidBrush::SolidBrush()
	: SolidBrush(RGB(0,0,0))
{
}

lycee::SolidBrush::SolidBrush(COLORREF crColor)
	: color(crColor)
{
}

lycee::SolidBrush::SolidBrush(const SolidBrush &_Other)
	: color(_Other.color)
{
}

lycee::SolidBrush& lycee::SolidBrush::operator =(const SolidBrush& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
	}
	return *this;
}

HBRUSH lycee::SolidBrush::create() const
{
	return CreateSolidBrush(this->color);
}

// ====================================================================================
// Pencil
// ====================================================================================
lycee::Pencil::~Pencil()
{
}

lycee::Pencil::Pencil()
	: Pencil(RGB(0, 0, 0))
{
}

lycee::Pencil::Pencil(COLORREF crColor)
	: color(crColor),
	bkMode(PencilMode::Transparent)
{
}

lycee::Pencil::Pencil(const Pencil &_Other)
	: color(_Other.color),
	bkMode(_Other.bkMode)
{
}

lycee::Pencil& lycee::Pencil::operator =(const Pencil& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
		this->bkMode = _Other.bkMode;
	}
	return *this;
}

lycee::Pencil& lycee::Pencil::mode(lycee::Pencil::PencilMode pencilMode)
{
	this->bkMode = pencilMode;
	return *this;
}

BOOL lycee::Pencil::draw(HDC hdc, lycee::Pencil::gui_callback callback) const
{
	COLORREF crOldColor = SetTextColor(hdc, this->color);
	int oldMode = SetBkMode(hdc, this->bkMode);

	BOOL res = callback(hdc);

	SetBkMode(hdc, oldMode);
	SetTextColor(hdc, crOldColor);
	return res;
}

// ====================================================================================
// Font
// ====================================================================================
lycee::Font::~Font()
{
}

lycee::Font::Font(int size)
	: logFont({ 0 })
{
	this->initialize(size, Charset::DEFAULT, TEXT("Meiryo"));
}

lycee::Font::Font(int size, const lycee_string &faceName)
	: logFont({ 0 })
{
	this->initialize(size, Charset::DEFAULT, faceName);
}

lycee::Font::Font(int size, Charset charset)
	: logFont({ 0 })
{
	this->initialize(size, charset, TEXT(""));
}

void lycee::Font::initialize(int size, Charset charset, const lycee_string &faceName)
{
	logFont.lfHeight = size;				// font size
	logFont.lfWidth = 0L;

	logFont.lfEscapement = 0L;				// text angle (unit: degree)
	logFont.lfOrientation = 0L;				// text angle (unit: degree)

	logFont.lfWeight = FW_NORMAL;			// bold style
	logFont.lfItalic = FALSE;				// italic style
	logFont.lfUnderline = FALSE;			// underline style
	logFont.lfStrikeOut = FALSE;			// strikeout style

	logFont.lfCharSet = charset;			// charset

	logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;	// search precision
	logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;	// clipping precision
	logFont.lfQuality = DEFAULT_QUALITY;	// font quality

	logFont.lfPitchAndFamily = 0L;			// pitch and family

											// face name
	strcpy_s(logFont.lfFaceName, LF_FACESIZE, faceName.c_str());
}

lycee::Font::Font(const Font &_Other)
	: logFont({ 0 })
{
	memcpy_s(
		&this->logFont, sizeof(this->logFont),
		&_Other.logFont, sizeof(_Other.logFont));
}

lycee::Font& lycee::Font::operator =(const Font &_Other)
{
	if (this != &_Other) {
		memcpy_s(
			&this->logFont, sizeof(this->logFont),
			&_Other.logFont, sizeof(_Other.logFont));
	}
	return *this;
}

lycee::Font& lycee::Font::italic(bool bEnable)
{
	logFont.lfItalic = trif(bEnable, TRUE, FALSE);
	return *this;
}

lycee::Font& lycee::Font::bold(bool bEnable)
{
	logFont.lfWeight = trif(bEnable, FW_BOLD, FW_NORMAL);
	return *this;
}

lycee::Font& lycee::Font::underline(bool bEnable)
{
	logFont.lfUnderline = trif(bEnable, TRUE, FALSE);
	return *this;
}

lycee::Font& lycee::Font::strikeout(bool bEnable)
{
	logFont.lfStrikeOut = trif(bEnable, TRUE, FALSE);
	return *this;
}

BOOL lycee::Font::draw(HDC hdc, lycee::Font::gui_callback callback) const
{
	HFONT hFont = CreateFontIndirect(&this->logFont);
	if (hFont == NULL) {
		return FALSE;
	}
	HFONT hOldFont = SelectFont(hdc, hFont);
	
	BOOL res = callback(hdc);
	
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
	return res;
}