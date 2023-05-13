#include "Window.h"

#include <iostream>
#include "Mouse.h"

Window::Window(int width, int height)
{
	std::cout << "Init SDL2" << std::endl;

	int result = SDL_Init(SDL_INIT_VIDEO);
	if (result != 0)
	{
        throw std::runtime_error("SDL2 Init error");
	}

    std::cout << "Create Window" << std::endl;

	m_window = SDL_CreateWindow("Minimax",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		0);

	if (m_window == NULL)
	{
        throw std::runtime_error("Creating window error");
	}
}

Window::~Window()
{
	std::cout << "Destroy Window" << std::endl;
		
    SDL_DestroyWindow(m_window);
        
    std::cout << "Quit SDL2" << std::endl;
	
    SDL_Quit();
}

bool Window::update()
{
    Mouse::wasLeftDown = Mouse::isLeftDown;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			Mouse::x = event.button.x;
			Mouse::y = event.button.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                Mouse::isLeftDown = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                Mouse::isLeftDown = false;
            }
            break;
		case SDL_QUIT:
            return false;
			break;
		}
	}

    return true;
}
