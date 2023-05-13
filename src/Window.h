#ifndef DEF_WINDOW
#define DEF_WINDOW

#include "SDL2/SDL.h"

class Window
{
public:
	Window(int width, int height);
	~Window();

	bool update();

private:
	friend class GraphicsManager;

	SDL_Window* m_window;
};

#endif