#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include <math.h>

#include <SDL2/SDL.h>

namespace graphics {

Uint32 formatColour(const Uint8 &red, const Uint8 &green, const Uint8 &blue);

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

		Uint32* m_buffer;

		std::string SCREEN_NAME;

	public:
		static size_t getScreenWidth() { return SCREEN_WIDTH; };
		static size_t getScreenHeight() { return SCREEN_HEIGHT; };
		static size_t getPixels() { return PIXELS; };

		SDL_Window* getWindow() const { return this->m_window; };

		Uint32* getBuffer() { return this->m_buffer; };

		Screen(const std::string &sn) { this->SCREEN_NAME = sn; };
		~Screen() {
			SDL_DestroyTexture(this->m_texture);
			SDL_DestroyRenderer(this->m_renderer);
			SDL_DestroyWindow(this->m_window);
			delete [] m_buffer;
		};

		// IMPLEMENTATION IN CPP FILE
		bool init();
		bool processEvents();
		void update();
		void makeGreyScale(const short &a);
		void makePlainColour(const Uint8 &red, const Uint8 &green, const Uint8 &blue);
		void setPixel(const Uint16 &x, const Uint16 &y, const Uint8 &red, const Uint8 &green, const Uint8 &blue);

};

class Particle {

	private:
		double pos_x;
		double pos_y;
		Uint32 colour;

	public:
		Particle(const double &x, const double &y):
			pos_x(x),
			pos_y(y)
		{
			this->updateColour();
		};
		void updateColour();
};

class Swarm {

	private:


	public:


};

}

#endif
