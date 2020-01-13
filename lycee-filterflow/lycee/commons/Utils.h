#ifndef __LYCEE__UTILS__HEADER__
#define __LYCEE__UTILS__HEADER__

#include "..\includes.h"


namespace lycee {

	namespace commons {

		class Strings {
		private:
			~Strings() { }
			Strings() { }
			Strings(const Strings &) { }
			Strings& operator =(const Strings &) { return *this;  }

		public:
			template<typename char_type>
			static std::optional<std::basic_string<char_type>> format(const std::basic_string<char_type> &fmt, va_list args) {
				return _format(fmt, args);
			}

			template<>
			static std::optional<std::basic_string<wchar_t>> format<wchar_t>(const std::basic_string<wchar_t> &fmt, va_list args) {
				return _wformat(fmt, args);
			}

		private:
			static std::optional<std::string> _format(std::string fmt, std::va_list vargs);

			static std::optional<std::wstring> _wformat(std::wstring fmt, std::va_list vargs);
		};


	}	// commons

}	// lycee
#endif	// __LYCEE__UTILS__HEADER__
