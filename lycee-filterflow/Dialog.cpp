#include "Dialog.h"

#include "Utils.h"

// ============================================================================
// FileSelectDialog
// ============================================================================
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


// ============================================================================
// MessageDialog
// ============================================================================

lycee::MessageDialog::~MessageDialog()
{
	;
}

lycee::MessageDialog::MessageDialog()
	: strTitle(TEXT("lycee::MessageDialog")),
	strMsg(TEXT("Message")),
	buttonType(lycee::MessageDialog::ButtonType::Ok),
	iconType(lycee::MessageDialog::IconType::NoUse)
{
	;
}

lycee::MessageDialog& lycee::MessageDialog::title(const lycee_string &str)
{
	strTitle = str;
	return *this;
}

lycee::MessageDialog& lycee::MessageDialog::message(lycee_string fmt, ...)
{
	std::va_list args;
	va_start(args, fmt);
	auto text = lycee::Strings::format(fmt, args);

	if (text) {
		this->strMsg = text.value();
	}
	va_end(args);
	return *this;
}

lycee::MessageDialog& lycee::MessageDialog::button(ButtonType type)
{
	buttonType = type;
	return *this;
}

lycee::MessageDialog& lycee::MessageDialog::icon(IconType type)
{
	iconType = type;
	return *this;
}

int lycee::MessageDialog::show(HWND hParentWnd)
{
	return MessageBox(
		hParentWnd,
		strMsg.c_str(),
		strTitle.c_str(),
		buttonType | iconType
	);
}

int lycee::MessageDialog::info(HWND hWnd, lycee_string fmt, ...)
{
	std::va_list args;
	va_start(args, fmt);
	auto message = lycee::Strings::format(fmt, args);
	va_end(args);

	return lycee::MessageDialog()
		.title(TEXT("Information"))
		.message(message.value())
		.button(ButtonType::Ok)
		.icon(IconType::Information)
		.show(hWnd);
}

int lycee::MessageDialog::error(HWND hWnd, lycee_string fmt, ...)
{
	std::va_list args;
	va_start(args, fmt);
	auto message = lycee::Strings::format(fmt, args);
	va_end(args);

	return lycee::MessageDialog()
		.title(TEXT("Error!!"))
		.message(message.value())
		.button(ButtonType::Ok)
		.icon(IconType::Stop)
		.show(hWnd);
}

int lycee::MessageDialog::confirm(HWND hWnd, lycee_string fmt, ...)
{
	std::va_list args;
	va_start(args, fmt);
	auto message = lycee::Strings::format(fmt, args);
	va_end(args);

	return lycee::MessageDialog()
		.title(TEXT("Confirmation"))
		.message(message.value())
		.button(ButtonType::OkCancel)
		.icon(IconType::Question)
		.show(hWnd);
}

int lycee::MessageDialog::warning(HWND hWnd, lycee_string fmt, ...)
{
	std::va_list args;
	va_start(args, fmt);
	auto message = lycee::Strings::format(fmt, args);
	va_end(args);

	return lycee::MessageDialog()
		.title(TEXT("Warning!!"))
		.message(message.value())
		.button(ButtonType::Ok)
		.icon(IconType::Exclamation)
		.show(hWnd);
}

int lycee::MessageDialog::retry(HWND hWnd, lycee_string fmt, ...)
{
	std::va_list args;
	va_start(args, fmt);
	auto message = lycee::Strings::format(fmt, args);
	va_end(args);

	return lycee::MessageDialog()
		.title(TEXT("Retry or Cancel?"))
		.message(message.value())
		.button(ButtonType::RetryCancel)
		.icon(IconType::Question)
		.show(hWnd);
}


// ============================================================================
// ColorPicker
// ============================================================================

lycee::ColorPicker::~ColorPicker()
{
	delete[] cc.lpCustColors;
}

lycee::ColorPicker::ColorPicker()
	: cc({ 0 })
{
	cc.lStructSize = sizeof(cc);
	cc.lpCustColors = new COLORREF[16];
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.rgbResult = 0;
}

lycee::ColorPicker& lycee::ColorPicker::initColor(COLORREF color)
{
	this->cc.rgbResult = color;
	return *this;
}

std::optional<COLORREF> lycee::ColorPicker::show(HWND hParentWnd)
{
	cc.hwndOwner = hParentWnd;

	std::optional<COLORREF> result;

	if (ChooseColor(&cc)) {
		result = cc.rgbResult;
	}
	return result;
}
