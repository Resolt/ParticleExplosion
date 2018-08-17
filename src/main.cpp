#include "Util.hpp"
#include "Graphics.hpp"

int main()
{
	// SET UP SIG HANDLER
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = util::mySigHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	// START SOME GRAPHICS
	graphics::Screen *screen = new graphics::Screen("YEAHPLAYAH");
	if(!screen->init())
	{
		std::cout << "Couldn't create screen" << std::endl;
		delete screen;
		return 2;
	}

	bool quit = false;

	// SET COLOUR
	Uint32 c = 0x0FF0FF00;
	screen->makeColour(c, screen->getBuffer1());

	while(!quit)
	{
		// HANDLE SIGNALS
		sigaction(SIGINT, &sigIntHandler, NULL);

		quit = screen->processEvents();

		// WAIT FOR AN AMOUNT OF MILISECONDS
		SDL_Delay(25);
	}

	delete screen;

	SDL_Quit();

	return 0;
}
