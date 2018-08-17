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
	graphics::Screen *screen = new graphics::Screen("Windows Media Player Animation And Shit");
	if(!screen->init())
	{
		std::cout << "Couldn't create screen" << std::endl;
		delete screen;
		SDL_Quit();
		return 2;
	}

	bool quit = false;

	screen->makePlainColour(255, 255, 0);
	screen->update();

	while(!quit)
	{
		// HANDLE SIGNALS
		sigaction(SIGINT, &sigIntHandler, NULL);

		quit = screen->processEvents();

		// WAIT FOR AN AMOUNT OF MILISECONDS
		// SDL_Delay(25);
	}

	delete screen;

	SDL_Quit();

	return 0;
}
