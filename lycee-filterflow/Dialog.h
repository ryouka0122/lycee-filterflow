#ifndef __LYCEE__DIALOG__HEADER__
#define __LYCEE__DIALOG__HEADER__

#include "includes.h"

#include <cstdarg>
#include <optional>

namespace lycee {
	
	class FileSelectDialog {
	public:
		virtual ~FileSelectDialog();
		FileSelectDialog();

		FileSelectDialog& title(const lycee_string &_title);

		FileSelectDialog& filter(const lycee_string &_ext, const lycee_string &_name);

		FileSelectDialog& basedir(const lycee_string &_basedir);

		std::optional<lycee_string> showSaveDialog(HWND hParentWnd);
		
		std::optional<lycee_string> showLoadDialog(HWND hParentWnd);

	private:
		lycee_string strTitle;
		std::list<std::pair<lycee_string, lycee_string>> filterList;
		lycee_string strBaseDir;

		std::optional<lycee_string> _show(HWND hParentWnd, DWORD dwFlags, std::function<BOOL(LPOPENFILENAME)> callback);

		LPTSTR buildFilter();

	};


	class MessageDialog {
	public:
		enum ButtonType {
			Ok					= MB_OK,
			OkCancel			= MB_OKCANCEL,
			AbortRetryIgnore	= MB_ABORTRETRYIGNORE,
			YesNo				= MB_YESNO,
			YesNoCancel			= MB_YESNOCANCEL,
			RetryCancel			= MB_RETRYCANCEL,
		};

		enum IconType {
			NoUse			= 0,
			Stop			= MB_ICONHAND,			// mark: x
			Question		= MB_ICONQUESTION,		// mark: ?
			Exclamation		= MB_ICONEXCLAMATION,	// mark: !
			Information		= MB_ICONASTERISK,		// mark: i
		};

	public:
		virtual ~MessageDialog();
		MessageDialog();

		MessageDialog& title(const lycee_string &str);
		MessageDialog& message(lycee_string fmt, ...);
		MessageDialog& button(ButtonType type);
		MessageDialog& icon(IconType type);
		
		int show(HWND hParentWnd);

	private:
		lycee_string strTitle;
		lycee_string strMsg;
		ButtonType buttonType;
		IconType iconType;
		
	public:
		static int info(HWND hWnd, lycee_string fmt, ...);
		static int error(HWND hWnd, lycee_string fmt, ...);
		static int confirm(HWND hWnd, lycee_string fmt, ...);
		static int warning(HWND hWnd, lycee_string fmt, ...);
		static int retry(HWND hWnd, lycee_string fmt, ...);

	};

	class ColorPicker {
	public:
		virtual ~ColorPicker();
		ColorPicker();

		ColorPicker& initColor(COLORREF color);
		std::optional<COLORREF> show(HWND hParentWnd);

		COLORREF& operator [](int i)
		{
			return cc.lpCustColors[i];
		}

		const COLORREF& operator [](int i) const
		{
			return cc.lpCustColors[i];
		}

	private:
		CHOOSECOLOR cc;
	};

}	// lycee
#endif	// __LYCEE__DIALOG__HEADER__
