#ifndef DEF_GRAPHICS_MANAGER
#define DEF_GRAPHICS_MANAGER

#include <string>
#include "SDL2/SDL.h"
#include "Window.h"
#include "Texture.h"
#include "Vector2.h"

class GraphicsManager
{
public:
	GraphicsManager(Window const& window);
	~GraphicsManager();

	void loadTexture(std::string path, Texture & texture) const;
	void drawTexture(Texture const& texture, Vector2 position, float scale) const;
	void render() const;
	void clearScreen() const;

private:
	SDL_Renderer* m_renderer;
};

#endif
