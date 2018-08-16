#include <iostream>

#include <SDL2/SDL.h>

const size_t SCREEN_WIDTH = 800;
const size_t SCREEN_HEIGHT = 600;

int main()
{
	// INIT SDL
	int sdlinit = SDL_Init(SDL_INIT_VIDEO);
	if(sdlinit < 0)
	{
		std::cout << "SDL INIT FAILED : " << sdlinit << std::endl;
		return 1;
	}
	else
	{
		std::cout << "SDL INIT SUCCEEDED" << std::endl;
	}

	// OPEN UP A WINDOW
	SDL_Window *window = SDL_CreateWindow(
		"LULZ",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	// CHECK THE WINDOWS STATUS
	if(window == NULL)
	{
		std::cout << "Window couldn't open : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 2;
	}

	// 3 SECOND DELAY
	SDL_Delay(3000);

	// QUIT SDL AND RETURN
	SDL_Quit();
	return 0;
}
