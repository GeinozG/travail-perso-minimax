#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include "SDL2/SDL.h"
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

private:
	friend class GraphicsManager;

	int m_width;
	int m_height;
	std::string m_path;

	SDL_Texture * m_texture;
};

#endif