#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include <math.h>

#include <SDL2/SDL.h>

namespace graphics {

Uint32 formatColour(const Uint8 &red, const Uint8 &green, const Uint8 &blue);

class Screen {

	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;
		SDL_Event event;

		Uint32* m_buffer;

		std::string SCREEN_NAME;

	public:
		static const size_t SCREEN_WIDTH = 800;
		static const size_t SCREEN_HEIGHT = 600;
		static const size_t PIXELS = SCREEN_WIDTH * SCREEN_HEIGHT;
		static const size_t MEMSIZE = PIXELS*sizeof(Uint32);
		static const size_t MEMSIZEROW = SCREEN_WIDTH*sizeof(Uint32);

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
		void setPixel(const Uint16 &x, const Uint16 &y, const Uint32 &colour);

};

class Particle {

	private:
		Uint32 colour;

	public:
		double pos_x = ((double)rand()/(double)RAND_MAX) * (double)Screen::SCREEN_WIDTH;
		double pos_y = ((double)rand()/(double)RAND_MAX) * (double)Screen::SCREEN_HEIGHT;

		Particle();
		void updateColour();
		void setColour(const Uint8 & red, const Uint8 &green, const Uint8 &blue) { this->colour = formatColour(red, green, blue); };
		Uint32 getColour() const { return this->colour; };

};

class Swarm {

	private:
		 Particle * const m_particles = new Particle[NPARTICLES];

	public:
		static const size_t NPARTICLES = 5000;

		Swarm();
		virtual ~Swarm() { delete [] m_particles; };
		Particle * const getParticles() const { return m_particles; };

};

}

#endif
