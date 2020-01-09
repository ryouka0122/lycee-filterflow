#include "Dialog.h"

lycee::FileSelectDialog::~FileSelectDialog()
{
}

lycee::FileSelectDialog::FileSelectDialog()
	: strTitle(TEXT("ファイル選択ダイアログ")),
	filterList(),
	strBaseDir()
{
	;
}

lycee::FileSelectDialog& lycee::FileSelectDialog::title(const lycee_string &_title)
{
	this->strTitle = _title;
	return *this;
}

lycee::FileSelectDialog& lycee::FileSelectDialog::filter(const lycee_string &_ext, const lycee_string &_name)
{
	for (auto iter = this->filterList.begin(); iter != this->filterList.end(); iter++) {
		if (iter->first == _ext) {
			iter->second = _name;
			return *this;
		}
	}
	this->filterList.push_back(std::make_pair(_ext, _name));
	return *this;
}

lycee::FileSelectDialog& lycee::FileSelectDialog::basedir(const lycee_string &_basedir)
{
	this->strBaseDir = _basedir;
	return *this;
}

std::optional<lycee_string> lycee::FileSelectDialog::showSaveDialog(HWND hParentWnd)
{
	return _show(hParentWnd, OFN_OVERWRITEPROMPT, GetSaveFileName);
}

std::optional<lycee_string> lycee::FileSelectDialog::showLoadDialog(HWND hParentWnd)
{
	return _show(hParentWnd, OFN_FILEMUSTEXIST, GetOpenFileName);
}

std::optional<lycee_string> lycee::FileSelectDialog::_show(HWND hParentWnd, DWORD dwFlags, std::function<BOOL(LPOPENFILENAME)> callback)
{
	std::optional<lycee_string> result;
	OPENFILENAME ofn = { 0 };
	TCHAR fileResult[1000] = { 0 };

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hParentWnd;
	ofn.hInstance = NULL;

	ofn.lpstrFilter = buildFilter();
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 256;
	ofn.nFilterIndex = 0L;
	
	ofn.lpstrFile = fileResult;
	ofn.nMaxFile = MAX_PATH;

	ofn.lpstrInitialDir = this->strBaseDir.c_str();
	ofn.lpstrTitle = this->strTitle.c_str();

	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;

	ofn.Flags = OFN_EXPLORER | dwFlags;

	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = NULL;

	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;

	BOOL bRes = callback(&ofn);

	if (bRes) {
		result.emplace(lycee_string(ofn.lpstrFile));
	}
	if (ofn.lpstrFilter) {
		delete[] ofn.lpstrFilter;
	}
	return result;
}

LPTSTR lycee::FileSelectDialog::buildFilter()
{
	lycee_string::size_type length = 1;	// for last `\0`

	std::list<std::list<lycee_string::value_type>> filterTextList;

	for (auto iter = this->filterList.begin(); iter != this->filterList.end(); iter++) {
		if (iter->first.empty() || iter->second.empty()) {
			continue;
		}
		std::list<lycee_string::value_type> text;
		lycee_string ext = TEXT("*.") + iter->first;
		lycee_string name = iter->second + TEXT("(") + ext + TEXT(")");
		text.insert(text.end(), name.begin(), name.end());
		text.push_back(0);
		text.insert(text.end(), ext.begin(), ext.end());
		text.push_back(0);

		length += text.size();
		filterTextList.push_back(text);
	}
	if (length == 1) {
		return NULL;
	}
	LPTSTR lpFilter = new TCHAR[length];
	memset(lpFilter, 0, sizeof(TCHAR) * length);
	LPTSTR cursor = lpFilter;
	
	lycee_string::size_type fpos;

	for (auto iter = filterTextList.begin(); iter != filterTextList.end(); iter++) {
		fpos = iter->size();
		for (auto p = iter->begin(); p != iter->end();) {
			*cursor++ = *p++;
		}
	}
	return lpFilter;
}

