#include <iostream>

#include <SDL2/SDL.h>

int main()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL INIT FAILED!" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Greetings morons!" << std::endl;
	}

	return 0;
}
