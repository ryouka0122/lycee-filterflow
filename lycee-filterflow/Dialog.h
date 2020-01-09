#ifndef __LYCEE__DIALOG__HEADER__
#define __LYCEE__DIALOG__HEADER__

#include "includes.h"

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


}	// lycee
#endif	// __LYCEE__DIALOG__HEADER__
