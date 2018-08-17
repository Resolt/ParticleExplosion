#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <signal.h>

// NAMESPACE UTIL
namespace util {

	// SIG HANDLER
	void mySigHandler(int s)
	{
		std::cout << "Caught signal " << s << std::endl;
		exit(1);
	}

}

#endif
