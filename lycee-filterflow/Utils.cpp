#include "Utils.h"



std::optional<std::string> lycee::Strings::_format(std::string fmt, std::va_list args)
{
	std::optional<std::string> result;

	int len = _vscprintf(fmt.c_str(), args) + 1;

	char *temp = (char*)malloc(len * sizeof(char));
	if (temp != NULL) {

		vsprintf_s(temp, len, fmt.c_str(), args);
		result = std::string(temp);
		free(temp);
	}
	return result;
}

std::optional<std::wstring> lycee::Strings::_wformat(std::wstring fmt, std::va_list args)
{
	std::optional<std::wstring> result;
	int len = _vscwprintf(fmt.c_str(), args) + 1;

	wchar_t *temp = (wchar_t*)malloc(len * sizeof(wchar_t));
	if (temp != NULL) {

		vswprintf_s(temp, len, fmt.c_str(), args);
		result = std::wstring(temp);
		free(temp);
	}
	return result;
}
