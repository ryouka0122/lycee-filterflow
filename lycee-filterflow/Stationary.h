#ifndef __LYCEE__STATIONARY__HEADER__
#define __LYCEE__STATIONARY__HEADER__

#include "includes.h"

namespace lycee {

	// ===========================================================================
	// GuiTool superclass
	//
	class GuiTool {
	public:
		typedef std::function<BOOL (HDC)> gui_callback;

	protected:
		virtual ~GuiTool() = 0 { }

	public:
		virtual BOOL draw(HDC hdc, gui_callback callback) const = 0;

	};


	// ===========================================================================
	// Pen class
	//
	class Pen : public virtual GuiTool {
	public:
		typedef typename GuiTool::gui_callback gui_callback;

		virtual ~Pen();

		Pen();
		Pen(COLORREF crColor);
		Pen(COLORREF crColor, int cWidth);
		Pen(COLORREF crColor, int cWidth, int iStyle);

		Pen(const Pen &_Other);
		Pen& operator =(const Pen& _Other);

	public:
		virtual BOOL draw(HDC hdc, gui_callback callback) const;

	private:
		COLORREF color;
		int width;
		int style;
	};


	// ===========================================================================
	// Brush class
	//
	class Brush : public virtual GuiTool {
	public:
		typedef typename GuiTool::gui_callback gui_callback;
		
	protected:
		virtual ~Brush() = 0 { }

	public:
		virtual BOOL draw(HDC hdc, gui_callback callback) const;

	protected:
		virtual HBRUSH create() const = 0;

	};

	class SolidBrush : public virtual Brush {
	public:
		typedef typename Brush::gui_callback gui_callback;

		virtual ~SolidBrush();

		SolidBrush();
		SolidBrush(COLORREF crColor);

		SolidBrush(const SolidBrush &_Other);
		SolidBrush& operator =(const SolidBrush& _Other);

	protected:
		virtual HBRUSH create() const;

	private:
		COLORREF color;
	};


	// ===========================================================================
	// Pencil class
	//
	class Pencil : public virtual GuiTool {
	public:
		typedef typename GuiTool::gui_callback gui_callback;

		enum PencilMode {
			Opaque = OPAQUE,
			Transparent = TRANSPARENT,
		};

		virtual ~Pencil();

		Pencil();
		Pencil(COLORREF crColor);

		Pencil(const Pencil &_Other);
		Pencil& operator =(const Pencil& _Other);

	public:
		Pencil& mode(PencilMode pencilMode);

		virtual BOOL draw(HDC hdc, gui_callback callback) const;

	private:
		COLORREF color;
		PencilMode bkMode;
	};

	// ===========================================================================
	// Font class
	//
	class Font : public virtual GuiTool {
	public:
		typedef typename GuiTool::gui_callback gui_callback;

		enum Charset {
			ANSI = ANSI_CHARSET,
			DEFAULT = DEFAULT_CHARSET,
			ShiftJIS = SHIFTJIS_CHARSET,
		};

		virtual ~Font();

		Font();
		Font(int size);
		Font(const lycee_string &faceName);
		Font(Charset charset);
		Font(int size, const lycee_string &faceName);
		Font(int size, Charset charset);

	private:
		enum { DefaultFontSize = 16 };
		void initialize(int size, Charset charset, const lycee_string &faceName);

	public:
		Font(const Font &_Other);
		Font& operator =(const Font &_Other);

	public:
		Font& size(int szHeight);
		Font& italic(bool bEnable);
		Font& bold(bool bEnable);
		Font& underline(bool bEnable);
		Font& strikeout(bool bEnable);

		virtual BOOL draw(HDC hdc, gui_callback callback) const;

	private:
		LOGFONT logFont;

	};


}	// lycee
#endif	// __LYCEE__STATIONARY__HEADER__
