#include <iostream>

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
	graphics::Screen *screen = new graphics::Screen;
	screen->init();

	bool quit = false;
	SDL_Event event;

	while(!quit)
	{
		// HANDLE SIGNALS
		sigaction(SIGINT, &sigIntHandler, NULL);

		while(SDL_PollEvent(&event))
		{
			// HANDLE SDL EVENTS
			if(event.type == SDL_QUIT)
			{
				quit = true;
				continue;
			}
		}
	}

	// 3 SECOND DELAY
	// SDL_Delay(3000);

	// DESTROY WINDOW
	// SDL_DestroyWindow(window);
	// QUIT SDL
	SDL_Quit();

	return 0;
}
