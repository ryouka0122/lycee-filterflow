#ifndef __LYCEE__IMAGE__HEADER__
#define __LYCEE__IMAGE__HEADER__

#include "includes.h"

namespace lycee {

	class Image {
	public:
		virtual ~Image();
		Image();
		
		Image clone() const;

	private:

	};


}	// lycee
#endif	// __LYCEE__IMAGE__HEADER__
