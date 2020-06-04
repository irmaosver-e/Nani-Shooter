#include "SDLSystem.h"
#include "SystemParser.h"
#include <iostream>

SDLSystem::SDLSystem(token) : m_pWindow(nullptr), m_pRenderer(nullptr), m_frameTime(0.0f), m_fps(60)
{
}

SDLSystem::~SDLSystem()
{
	// we must clean up after ourselves to prevent memory leaks
	m_pRenderer = nullptr;
	m_pWindow = nullptr;
}

bool SDLSystem::init(const char* title, int windowXpos, int windowYpos, int screenWidth, int screenHeight, int fps, bool fullScreen,
						int drawColour_R, int drawColour_G, int drawColour_B, int drawColour_A)
{
	m_fps = fps;

	//sets flag to fullscreen
	int flags = 0;

	if (fullScreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	//attempt to initialize SDL if not present
	if (!SDL_Init(SDL_INIT_EVERYTHING))
	{
		//init the window
		m_pWindow = SDL_CreateWindow(title, windowXpos, windowYpos, screenWidth, screenHeight, flags);

		if (m_pWindow) //window init success
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer) //renderer init success
			{
				SDL_SetRenderDrawColor(m_pRenderer, drawColour_R, drawColour_G, drawColour_B, drawColour_A);
			}
			else
			{
				std::cout << "SDLSystem::init initialize RENDERER fail\n";
				return false; //renderer init fail
			}
		}
		else
		{
			std::cout << "SDLSystem::init initialize WINDOW fail\n";
			return false; //window init fail
		}
	}
	else
	{
		std::cout << "SDLSystem::init fail\n";
		return false; // sdl init fail
	}

	return true;
}

bool SDLSystem::capFrameRate()
{	
	static int lastTime = SDL_GetTicks();
	int thisTime = SDL_GetTicks();
	m_frameTime += (float)(thisTime - lastTime);

	if (m_frameTime >= (1000.f / m_fps))
	{
		//std::cout << "ALLOWED frame - FPS: " << (1000 / m_frameTime) << "\n";
		m_frameTime = 0.0f;
		lastTime = thisTime;
		return true;
	}

	lastTime = thisTime;
	return false;
}

void SDLSystem::quit()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
