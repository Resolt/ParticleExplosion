#include "Graphics.hpp"

namespace graphics {

// FUNCTIONS

Uint32 formatColour(const Uint8 &red, const Uint8 &green, const Uint8 &blue)
{
	Uint32 colour = 0;

	colour += red;
	colour <<= 8;
	colour += green;
	colour <<= 8;
	colour += blue;
	colour <<= 8;
	colour += 0xFF;

	return colour;
}

// SCREEN

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

	m_buffer = new Uint32[PIXELS];

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

void Screen::update()
{
	SDL_UpdateTexture(this->m_texture, NULL, this->m_buffer, MEMSIZEROW);
	// SDL_RenderClear(this->m_renderer); // I'M SOMEWHAT SURE THAT THIS IN MANY CASES IS RATHER UNNECESSARY
	SDL_RenderCopy(this->m_renderer, this->m_texture, NULL, NULL);
	SDL_RenderPresent(this->m_renderer);
}

void Screen::makeGreyScale(const short &a)
{
	memset(this->m_buffer, a, MEMSIZE);
}

void Screen::makePlainColour(const Uint8 &red, const Uint8 &green, const Uint8 &blue)
{

	Uint32 colour = formatColour(red, green, blue);

	for(size_t i = 0; i < PIXELS; i ++)
	{
		this->m_buffer[i] = colour;
	}
}

void Screen::setPixel(const Uint16 &x, const Uint16 &y, const Uint8 &red, const Uint8 &green, const Uint8 &blue)
{
	this->m_buffer[(y * SCREEN_WIDTH) + x] = formatColour(red, green, blue);
}

void Screen::setPixel(const Uint16 &x, const Uint16 &y, const Uint32 &colour)
{
	this->m_buffer[(y * SCREEN_WIDTH) + x] = colour;
}

void Screen::drawParticles(const Particle *pParticles)
{
	for(size_t i = 0; i < Swarm::NPARTICLES; i++)
	{
		if(!pParticles[i].isOut)
		{
			this->setPixel((Uint16)round(pParticles[i].pos_x), (Uint16)round(pParticles[i].pos_y), pParticles[i].getColour());
		}
	}
	this->update();
}

// PARTICLE

void Particle::init(const bool &explosion)
{
	this->velocity = ((double)rand()/(double)RAND_MAX) * 2.99 + 0.01; // SET VELOCITY BETWEEN 0.5 and 3.0
	this->rad = ((double)rand()/(double)RAND_MAX) * 2 * M_PI; // SET RANDOM DIRECTION OF MOVEMENT
	this->h_speed = cos(this->rad) * this->velocity;
	this->v_speed = sin(this->rad) * this->velocity;

	if(explosion)
	{
		this->pos_x = (double)SCREEN_WIDTH/2;
		this->pos_y = (double)SCREEN_HEIGHT/2;
		// this->pos_x = ((double)rand()/(double)RAND_MAX) * (double)SCREEN_WIDTH * 0.005 + (double)SCREEN_WIDTH / 2.01;
		// this->pos_y = ((double)rand()/(double)RAND_MAX) * (double)SCREEN_HEIGHT * 0.005 + (double)SCREEN_HEIGHT / 2.01;
		// this->velocity =
		// 	(sqrt(pow(std::abs((int)this->pos_x - (int)SCREEN_WIDTH/2), 2) + pow(std::abs((int)this->pos_y - (int)SCREEN_WIDTH/2), 2)) /
		// 	((SCREEN_WIDTH + SCREEN_HEIGHT) / 2)) * 1;
		// this->rad = cos((SCREEN_HEIGHT/2 - this->pos_y) / (SCREEN_WIDTH/2 - this->pos_x));
		// if(this->pos_x < SCREEN_WIDTH/2)
		// {
		// 	this->rad = M_PI - this->rad;
		// }
	}
	else
	{
		this->pos_x = ((double)rand()/(double)RAND_MAX) * ((double)SCREEN_WIDTH - 1 - velocity*2) + velocity; // SET RANDOM POSITION
		this->pos_y = ((double)rand()/(double)RAND_MAX) * ((double)SCREEN_HEIGHT - 1 - velocity*2) + velocity;
	}
}

void Particle::updateColour()
{
	int ticks = SDL_GetTicks();

	Uint8 green = Uint8((1 + cos(ticks * 0.0001)) * 128);
	Uint8 red = Uint8((1 + cos(ticks * 0.0002)) * 128);
	Uint8 blue = Uint8((1 + cos(ticks * 0.0003)) * 128);

	this->colour = formatColour(red, green, blue);
}

void Particle::updatePos(const size_t &tdiff)
{
	// TEMPORARY VALUES
	double h_dist = this->h_speed * tdiff * this->speedMod;
	double v_dist = this->v_speed * tdiff * this->speedMod;

	bool setOut = false;

	this->pos_x += h_dist;
	this->pos_y += v_dist;

	// UPDATE DIRECTION RADIAN BASED ON HORISONTAL MOVEMENT
	if(this->pos_x < 0 || this->pos_x > SCREEN_WIDTH - 1)
	{
		this->h_speed = -this->h_speed;
		setOut = true;
	}

	// UPDATE DIRECTION RADIAN BASED ON VERTICAL MOVEMENT
	if(this->pos_y < 0 || this->pos_y > SCREEN_HEIGHT - 1)
	{
		this->v_speed = -this->v_speed;
		setOut = true;
	}

	this->isOut = setOut;
}

// SWARM

void Swarm::updatePositions()
{
	this->updateElapsed();
	for(size_t i = 0; i < NPARTICLES; i++)
	{
		m_particles[i].updatePos(this->tdiff);
	}
}

void Swarm::updateColours()
{
	for(size_t i = 0; i < NPARTICLES; i++)
	{
		m_particles[i].updateColour();
	}
}

void Swarm::updateElapsed()
{
	Uint32 celapsed = SDL_GetTicks();
	this->tdiff = (size_t)(celapsed - this->elapsed);
	this->elapsed = celapsed;

	// std::cout << this->elapsed << std::endl;
}

} /*namespace graphics*/
