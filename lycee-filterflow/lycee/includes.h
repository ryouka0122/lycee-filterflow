#ifndef __LYCEE__INCLUDES__HEADER__
#define __LYCEE__INCLUDES__HEADER__


#include <Windows.h>
#include <WindowsX.h>

#include <cstdarg>

#include <optional>
#include <functional>

#include <deque>
#include <list>
#include <map>

#include <string>

#include <opencv2\opencv.hpp>


typedef std::basic_string<TCHAR> lycee_string;

#define trif(cond, trueState, falseState)	(cond) ? (trueState) : (falseState)
#define GRAY(v)		RGB((v), (v), (v))



#endif	// __LYCEE__INCLUDES__HEADER__
