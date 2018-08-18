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
		exit(2);
	}

	void setSig()
	{
		// SET UP SIG HANDLER
		struct sigaction sigIntHandler;
		sigIntHandler.sa_handler = util::mySigHandler;
		sigemptyset(&sigIntHandler.sa_mask);
		sigIntHandler.sa_flags = 0;
		sigaction(SIGINT, &sigIntHandler, NULL);
	}

	void seedRand()
	{
		// SEED RAND
		srand(time(NULL));
	}

}

#endif
