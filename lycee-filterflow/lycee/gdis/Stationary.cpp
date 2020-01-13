#include "Stationary.h"

// ====================================================================================
// Pen
// ====================================================================================
lycee::gdis::Pen::~Pen()
{
}

lycee::gdis::Pen::Pen()
	: Pen(RGB(0,0,0), 1, PS_SOLID)
{
}

lycee::gdis::Pen::Pen(COLORREF crColor)
	: Pen(crColor, 1, PS_SOLID)
{
}

lycee::gdis::Pen::Pen(COLORREF crColor, int cWidth)
	: Pen(crColor, cWidth, PS_SOLID)
{
}

lycee::gdis::Pen::Pen(COLORREF crColor, int cWidth, int iStyle)
	: color(crColor),
	width(cWidth),
	style(iStyle)
{
}

lycee::gdis::Pen::Pen(const Pen &_Other)
	: color(_Other.color),
	width(_Other.width),
	style(_Other.style)
{
}

lycee::gdis::Pen& lycee::gdis::Pen::operator =(const Pen& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
		this->width = _Other.width;
		this->style = _Other.style;
	}
	return *this;
}

BOOL lycee::gdis::Pen::draw(HDC hdc, lycee::gdis::Pen::gui_callback callback) const
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

BOOL lycee::gdis::Brush::draw(HDC hdc, lycee::gdis::SolidBrush::gui_callback callback) const
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

lycee::gdis::SolidBrush::~SolidBrush()
{
}

lycee::gdis::SolidBrush::SolidBrush()
	: SolidBrush(RGB(0,0,0))
{
}

lycee::gdis::SolidBrush::SolidBrush(COLORREF crColor)
	: color(crColor)
{
}

lycee::gdis::SolidBrush::SolidBrush(const SolidBrush &_Other)
	: color(_Other.color)
{
}

lycee::gdis::SolidBrush& lycee::gdis::SolidBrush::operator =(const SolidBrush& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
	}
	return *this;
}

HBRUSH lycee::gdis::SolidBrush::create() const
{
	return CreateSolidBrush(this->color);
}

// ====================================================================================
// Pencil
// ====================================================================================
lycee::gdis::Pencil::~Pencil()
{
}

lycee::gdis::Pencil::Pencil()
	: Pencil(RGB(0, 0, 0))
{
}

lycee::gdis::Pencil::Pencil(COLORREF crColor)
	: color(crColor),
	bkMode(PencilMode::Transparent)
{
}

lycee::gdis::Pencil::Pencil(const Pencil &_Other)
	: color(_Other.color),
	bkMode(_Other.bkMode)
{
}

lycee::gdis::Pencil& lycee::gdis::Pencil::operator =(const Pencil& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
		this->bkMode = _Other.bkMode;
	}
	return *this;
}

lycee::gdis::Pencil& lycee::gdis::Pencil::mode(lycee::gdis::Pencil::PencilMode pencilMode)
{
	this->bkMode = pencilMode;
	return *this;
}

BOOL lycee::gdis::Pencil::draw(HDC hdc, lycee::gdis::Pencil::gui_callback callback) const
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
lycee::gdis::Font::~Font()
{
}

lycee::gdis::Font::Font()
	: logFont({ 0 })
{
	this->initialize(DefaultFontSize, Charset::DEFAULT, TEXT("Meiryo"));
}

lycee::gdis::Font::Font(int size)
	: logFont({ 0 })
{
	this->initialize(size, Charset::DEFAULT, TEXT("Meiryo"));
}

lycee::gdis::Font::Font(const lycee_string &faceName)
	: logFont({ 0 })
{
	this->initialize(DefaultFontSize, Charset::DEFAULT, faceName);
}

lycee::gdis::Font::Font(Charset charset)
	: logFont({ 0 })
{
	this->initialize(DefaultFontSize, charset, TEXT(""));
}

lycee::gdis::Font::Font(int size, const lycee_string &faceName)
	: logFont({ 0 })
{
	this->initialize(size, Charset::DEFAULT, faceName);
}

lycee::gdis::Font::Font(int size, Charset charset)
	: logFont({ 0 })
{
	this->initialize(size, charset, TEXT(""));
}

void lycee::gdis::Font::initialize(int size, Charset charset, const lycee_string &faceName)
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
#if defined(UNICODE) || defined(_UNICODE)
	wcscpy_s(logFont.lfFaceName, LF_FACESIZE, faceName.c_str());
#else
	strcpy_s(logFont.lfFaceName, LF_FACESIZE, faceName.c_str());
#endif
}

lycee::gdis::Font::Font(const Font &_Other)
	: logFont({ 0 })
{
	memcpy_s(
		&this->logFont, sizeof(this->logFont),
		&_Other.logFont, sizeof(_Other.logFont));
}

lycee::gdis::Font& lycee::gdis::Font::operator =(const Font &_Other)
{
	if (this != &_Other) {
		memcpy_s(
			&this->logFont, sizeof(this->logFont),
			&_Other.logFont, sizeof(_Other.logFont));
	}
	return *this;
}

lycee::gdis::Font& lycee::gdis::Font::size(int szHeight)
{
	logFont.lfHeight = szHeight;
	return *this;
}

lycee::gdis::Font& lycee::gdis::Font::italic(bool bEnable)
{
	logFont.lfItalic = trif(bEnable, TRUE, FALSE);
	return *this;
}

lycee::gdis::Font& lycee::gdis::Font::bold(bool bEnable)
{
	logFont.lfWeight = trif(bEnable, FW_BOLD, FW_NORMAL);
	return *this;
}

lycee::gdis::Font& lycee::gdis::Font::underline(bool bEnable)
{
	logFont.lfUnderline = trif(bEnable, TRUE, FALSE);
	return *this;
}

lycee::gdis::Font& lycee::gdis::Font::strikeout(bool bEnable)
{
	logFont.lfStrikeOut = trif(bEnable, TRUE, FALSE);
	return *this;
}

BOOL lycee::gdis::Font::draw(HDC hdc, lycee::gdis::Font::gui_callback callback) const
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