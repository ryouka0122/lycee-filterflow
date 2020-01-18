#include "Stationary.h"

// ====================================================================================
// Pen
// ====================================================================================
lycee::graphics::Pen::~Pen()
{
}

lycee::graphics::Pen::Pen()
	: Pen(RGB(0,0,0), 1, PS_SOLID)
{
}

lycee::graphics::Pen::Pen(COLORREF crColor)
	: Pen(crColor, 1, PS_SOLID)
{
}

lycee::graphics::Pen::Pen(COLORREF crColor, int cWidth)
	: Pen(crColor, cWidth, PS_SOLID)
{
}

lycee::graphics::Pen::Pen(COLORREF crColor, int cWidth, int iStyle)
	: color(crColor),
	width(cWidth),
	style(iStyle)
{
}

lycee::graphics::Pen::Pen(const Pen &_Other)
	: color(_Other.color),
	width(_Other.width),
	style(_Other.style)
{
}

lycee::graphics::Pen& lycee::graphics::Pen::operator =(const Pen& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
		this->width = _Other.width;
		this->style = _Other.style;
	}
	return *this;
}

BOOL lycee::graphics::Pen::draw(HDC hdc, lycee::graphics::Pen::gui_callback callback) const
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

BOOL lycee::graphics::Brush::draw(HDC hdc, lycee::graphics::SolidBrush::gui_callback callback) const
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

lycee::graphics::SolidBrush::~SolidBrush()
{
}

lycee::graphics::SolidBrush::SolidBrush()
	: SolidBrush(RGB(0,0,0))
{
}

lycee::graphics::SolidBrush::SolidBrush(COLORREF crColor)
	: color(crColor)
{
}

lycee::graphics::SolidBrush::SolidBrush(const SolidBrush &_Other)
	: color(_Other.color)
{
}

lycee::graphics::SolidBrush& lycee::graphics::SolidBrush::operator =(const SolidBrush& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
	}
	return *this;
}

HBRUSH lycee::graphics::SolidBrush::create() const
{
	return CreateSolidBrush(this->color);
}

// ====================================================================================
// Pencil
// ====================================================================================
lycee::graphics::Pencil::~Pencil()
{
}

lycee::graphics::Pencil::Pencil()
	: Pencil(RGB(0, 0, 0))
{
}

lycee::graphics::Pencil::Pencil(COLORREF crColor)
	: color(crColor),
	bkMode(PencilMode::Transparent)
{
}

lycee::graphics::Pencil::Pencil(const Pencil &_Other)
	: color(_Other.color),
	bkMode(_Other.bkMode)
{
}

lycee::graphics::Pencil& lycee::graphics::Pencil::operator =(const Pencil& _Other)
{
	if (this != &_Other) {
		this->color = _Other.color;
		this->bkMode = _Other.bkMode;
	}
	return *this;
}

lycee::graphics::Pencil& lycee::graphics::Pencil::mode(lycee::graphics::Pencil::PencilMode pencilMode)
{
	this->bkMode = pencilMode;
	return *this;
}

BOOL lycee::graphics::Pencil::draw(HDC hdc, lycee::graphics::Pencil::gui_callback callback) const
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
lycee::graphics::Font::~Font()
{
}

lycee::graphics::Font::Font()
	: logFont({ 0 })
{
	this->initialize(DefaultFontSize, Charset::DEFAULT, TEXT("Meiryo"));
}

lycee::graphics::Font::Font(int size)
	: logFont({ 0 })
{
	this->initialize(size, Charset::DEFAULT, TEXT("Meiryo"));
}

lycee::graphics::Font::Font(const lycee_string &faceName)
	: logFont({ 0 })
{
	this->initialize(DefaultFontSize, Charset::DEFAULT, faceName);
}

lycee::graphics::Font::Font(Charset charset)
	: logFont({ 0 })
{
	this->initialize(DefaultFontSize, charset, TEXT(""));
}

lycee::graphics::Font::Font(int size, const lycee_string &faceName)
	: logFont({ 0 })
{
	this->initialize(size, Charset::DEFAULT, faceName);
}

lycee::graphics::Font::Font(int size, Charset charset)
	: logFont({ 0 })
{
	this->initialize(size, charset, TEXT(""));
}

void lycee::graphics::Font::initialize(int size, Charset charset, const lycee_string &faceName)
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

lycee::graphics::Font::Font(const Font &_Other)
	: logFont({ 0 })
{
	memcpy_s(
		&this->logFont, sizeof(this->logFont),
		&_Other.logFont, sizeof(_Other.logFont));
}

lycee::graphics::Font& lycee::graphics::Font::operator =(const Font &_Other)
{
	if (this != &_Other) {
		memcpy_s(
			&this->logFont, sizeof(this->logFont),
			&_Other.logFont, sizeof(_Other.logFont));
	}
	return *this;
}

lycee::graphics::Font& lycee::graphics::Font::size(int szHeight)
{
	logFont.lfHeight = szHeight;
	return *this;
}

lycee::graphics::Font& lycee::graphics::Font::italic(bool bEnable)
{
	logFont.lfItalic = trif(bEnable, TRUE, FALSE);
	return *this;
}

lycee::graphics::Font& lycee::graphics::Font::bold(bool bEnable)
{
	logFont.lfWeight = trif(bEnable, FW_BOLD, FW_NORMAL);
	return *this;
}

lycee::graphics::Font& lycee::graphics::Font::underline(bool bEnable)
{
	logFont.lfUnderline = trif(bEnable, TRUE, FALSE);
	return *this;
}

lycee::graphics::Font& lycee::graphics::Font::strikeout(bool bEnable)
{
	logFont.lfStrikeOut = trif(bEnable, TRUE, FALSE);
	return *this;
}

BOOL lycee::graphics::Font::draw(HDC hdc, lycee::graphics::Font::gui_callback callback) const
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