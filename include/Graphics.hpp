#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include <iostream>

#include <math.h>

#include <SDL2/SDL.h>

namespace graphics {

static const Uint16 SCREEN_WIDTH = 1000;
static const Uint16 SCREEN_HEIGHT = 750;

Uint32 formatColour(const Uint8 &red, const Uint8 &green, const Uint8 &blue);

class Particle {

	private:

		static constexpr double speedMod = 0.005;

		Uint32 colour;

	public:

		double velocity;
		double rad;
		double pos_x;
		double pos_y;
		double h_speed;
		double v_speed;

		bool isOut = false;

		Particle() {};
		~Particle() {};
		void init(const bool &explosion);
		void updateColour();
		void updatePosLinear(const size_t &tdiff, const bool &border);
		void updatePosVortex(const size_t &tdiff, const bool &border);
		void updatePosPortal(const size_t &tdiff);
		void setColour(const Uint8 & red, const Uint8 &green, const Uint8 &blue) { this->colour = formatColour(red, green, blue); };
		Uint32 getColour() const { return this->colour; };

};

class Swarm {

	private:

		Particle * const m_particles = new Particle[NPARTICLES];
		Uint32 elapsed = SDL_GetTicks();
		size_t tdiff;

		bool border;
		size_t mode;

		void updateElapsed();

	public:

		static const size_t NPARTICLES = 2000;

		Swarm(const bool &explosion, const bool &border, const size_t &mode): border(border), mode(mode) { for(size_t i = 0; i < NPARTICLES; i++) { m_particles[i].init(explosion); }; };
		~Swarm() { delete [] m_particles; };
		Particle * const getParticles() const { return m_particles; };
		void updatePositions();
		void updateColours();

};

class Screen {

	private:

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;
		SDL_Event event;

		Uint32* m_buffer1;
		Uint32* m_buffer2;

		std::string SCREEN_NAME;

	public:

		static const size_t PIXELS = SCREEN_WIDTH * SCREEN_HEIGHT;
		static const size_t MEMSIZE = PIXELS*sizeof(Uint32);
		static const size_t MEMSIZEROW = SCREEN_WIDTH*sizeof(Uint32);

		SDL_Window* getWindow() const { return this->m_window; };

		Uint32* getBuffer1() { return this->m_buffer1; };
		Uint32* getBuffer2() { return this->m_buffer2; };

		Screen(const std::string &sn) { this->SCREEN_NAME = sn; };
		~Screen() {
			delete [] m_buffer1;
			delete [] m_buffer2;
		};
		void close() {
			SDL_DestroyWindow(this->m_window);
			SDL_DestroyRenderer(this->m_renderer);
			SDL_DestroyTexture(this->m_texture);
			SDL_Quit();
		};

		// IMPLEMENTATION IN CPP FILE
		bool init();
		bool processEvents();
		void update(Uint32 * buffer);
		void clear() { SDL_RenderClear(m_renderer); };
		void blur(Uint32 * srcBuffer, Uint32 * tmpBuffer, Uint32 * destBuffer, const size_t &boxWidth);
		void makeGreyScale(const short &a);
		void makePlainColour(const Uint8 &red, const Uint8 &green, const Uint8 &blue);
		void setPixel(const Uint16 &x, const Uint16 &y, const Uint8 &red, const Uint8 &green, const Uint8 &blue, Uint32 * buffer, const size_t &width);
		void setPixel(const Uint16 &x, const Uint16 &y, const Uint32 &colour, Uint32 * buffer, const size_t &width);
		void drawParticles(const Particle *pParticles, Uint32 * buffer, const size_t &width);

};

}

#endif
