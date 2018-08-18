#include "Util.hpp"
#include "Graphics.hpp"

int main()
{
	util::setSig();
	util::seedRand();

	// START SOME GRAPHICS
	graphics::Screen screen("Windows Media Player Animation And Shit");
	if(!screen.init())
	{
		std::cout << "Couldn't create screen" << std::endl;
		SDL_Quit();
		return 2;
	}

	bool quit = false;

	graphics::Swarm swarm(true, true, 1);

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
			std::cout << "\rFPS: " << (double)count/((double)tick/1000) << std::flush;
			tick = 0;
			count = 0;
		}

		// PROCESS SDL EVENTS INTO BOOL QUIT
		quit = screen.processEvents();

		// UPDATE THE PIXELS
		swarm.updatePositions();
		swarm.updateColours();
		// memset(screen.getBuffer1(), 0, graphics::Screen::MEMSIZE);
		screen.drawParticles(swarm.getParticles(), screen.getBuffer1(), 3);
		// memset(screen.getBuffer2(), 0, graphics::Screen::MEMSIZE);
		screen.blur(screen.getBuffer1(), screen.getBuffer2(), screen.getBuffer1(), 3);
		screen.update(screen.getBuffer1());
	}

	std::cout << std::endl;

	screen.close();

	return 0;
}
