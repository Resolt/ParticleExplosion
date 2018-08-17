#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>

#include <SDL2/SDL.h>

namespace graphics {

class Screen {

	private:
		static const size_t SCREEN_WIDTH = 800;
		static const size_t SCREEN_HEIGHT = 600;
		static const size_t PIXELS = SCREEN_WIDTH * SCREEN_HEIGHT;
		static const size_t MEMSIZE = PIXELS*sizeof(Uint32);
		static const size_t MEMSIZEROW = SCREEN_WIDTH*sizeof(Uint32);

		static const short RED_SHIFT = 24;
		static const short GREEN_SHIFT = 16;
		static const short BLUE_SHIFT = 8;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;
		SDL_Event event;

		Uint32* m_buffer1;
		Uint32* m_buffer2;
		Uint32* m_frontBuffer;
		Uint32* m_backBuffer;

		std::string SCREEN_NAME;

	public:
		static size_t getScreenWidth() { return SCREEN_WIDTH; };
		static size_t getScreenHeight() { return SCREEN_HEIGHT; };
		static size_t getPixels() { return PIXELS; };

		SDL_Window* getWindow() const { return this->m_window; };

		Uint32* getBuffer1() { return this->m_buffer1; };
		Uint32* getBuffer2() { return this->m_buffer2; };

		Screen(const std::string &sn) { this->SCREEN_NAME = sn; };
		~Screen() {
			SDL_DestroyTexture(this->m_texture);
			SDL_DestroyRenderer(this->m_renderer);
			SDL_DestroyWindow(this->m_window);
			delete [] m_buffer1;
			delete [] m_buffer2;
			delete [] m_frontBuffer;
			delete [] m_backBuffer;
		};

		// IMPLEMENTATION IN CPP FILE
		bool init();
		bool processEvents();
		void makeGreyScale(const short &a);
		void makeColour(const Uint32 &c, Uint32 *buffer);
		void setPixel(const size_t &bufferpos, const Uint32 &a, Uint32 *buffer);

};

}

#endif
