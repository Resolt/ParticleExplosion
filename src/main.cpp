#include "Util.hpp"
#include "Graphics.hpp"

int main()
{
	// SET UP SIG HANDLER
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = util::mySigHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	// SEED RAND
	srand(time(NULL));

	// START SOME GRAPHICS
	graphics::Screen screen("Windows Media Player Animation And Shit");
	if(!screen.init())
	{
		std::cout << "Couldn't create screen" << std::endl;
		SDL_Quit();
		return 2;
	}

	bool quit = false;

	graphics::Swarm swarm(true);

	// MAKE SCREEN BLACK
	screen.makePlainColour(0, 0, 0);

	// FPS CONTAINERS
	size_t tick = 0;
	Uint32 pel = SDL_GetTicks();
	Uint32 cel;
	size_t count = 0;

	while(!quit)
	{
		// GET SOME FPS
		count++;
		cel = SDL_GetTicks();
		tick += cel - pel;
		pel = cel;
		if(tick > 1000)
		{
			std::cout << "FPS: " << (double)count/((double)tick/1000) << std::endl;
			tick = 0;
			count = 0;
		}

		// HANDLE SIGNALS
		sigaction(SIGINT, &sigIntHandler, NULL);

		quit = screen.processEvents();

		// UPDATE THE PIXELS
		swarm.updatePositions();
		swarm.updateColours();
		memset(screen.getBuffer(), 0, graphics::Screen::MEMSIZE);
		screen.drawParticles(swarm.getParticles());
	}

	screen.close();

	return 0;
}
