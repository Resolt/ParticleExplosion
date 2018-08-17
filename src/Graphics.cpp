#include "Graphics.hpp"

namespace graphics {

bool Screen::init()
{
	m_window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}

	m_window = SDL_CreateWindow(
		this->SCREEN_NAME.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	m_texture = SDL_CreateTexture(
		m_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC,
		SCREEN_WIDTH,
		SCREEN_HEIGHT
	);

	if(m_window == NULL || SDL_GetError() == NULL || m_renderer == NULL || m_texture == NULL)
	{
		return false;
	}

	m_buffer1 = new Uint32[PIXELS];
	m_buffer2 = new Uint32[PIXELS];

	return true;
};

bool Screen::processEvents()
{
	// GET SDL EVENTS EVENT INTO event POINTER
	while(SDL_PollEvent(&this->event))
	{
		// HANDLE SDL EVENT
		if(event.type == SDL_QUIT)
		{
			return true;
		}
	}

	return false;
}

void Screen::makeGreyScale(const short &a)
{
	memset(this->m_buffer1, a, MEMSIZE);
	SDL_UpdateTexture(this->m_texture, NULL, this->m_buffer1, MEMSIZEROW);
	// SDL_RenderClear(this->m_renderer);
	SDL_RenderCopy(this->m_renderer, this->m_texture, NULL, NULL);
	SDL_RenderPresent(this->m_renderer);
}

void Screen::makeColour(const Uint32 &c, Uint32 *buffer)
{
	for(size_t i = 0; i < PIXELS; i ++)
	{
		buffer[i] = c;
	}
	SDL_UpdateTexture(this->m_texture, NULL, buffer, MEMSIZEROW);
	SDL_RenderCopy(this->m_renderer, this->m_texture, NULL, NULL);
	SDL_RenderPresent(this->m_renderer);
}

void Screen::setPixel(const size_t &bufferpos, const Uint32 &a, Uint32 *buffer)
{
	buffer[bufferpos] = a;
	SDL_UpdateTexture(this->m_texture, NULL, buffer, MEMSIZEROW);
	SDL_RenderCopy(this->m_renderer, this->m_texture, NULL, NULL);
	SDL_RenderPresent(this->m_renderer);
}

} /*namespace graphics*/
