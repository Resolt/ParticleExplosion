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
	graphics::Screen *screen = new graphics::Screen("Windows Media Player Animation And Shit");
	if(!screen->init())
	{
		std::cout << "Couldn't create screen" << std::endl;
		delete screen;
		SDL_Quit();
		return 2;
	}

	bool quit = false;

	screen->makePlainColour(0, 0, 0);
	screen->update();

	graphics::Swarm *swarm = new graphics::Swarm;

	graphics::Particle * const pParticles = swarm->getParticles();

	while(!quit)
	{
		// HANDLE SIGNALS
		sigaction(SIGINT, &sigIntHandler, NULL);

		quit = screen->processEvents();

		for(size_t i = 0; i < swarm->NPARTICLES; i++)
		{
			pParticles[i].updateColour();
			screen->setPixel(Uint16(pParticles[i].pos_x), Uint16(pParticles[i].pos_y), pParticles[i].getColour());
		}
		screen->update();

		// WAIT FOR AN AMOUNT OF MILISECONDS
		// SDL_Delay(25);
	}

	delete screen;
	delete swarm;

	SDL_Quit();

	return 0;
}
