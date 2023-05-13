#include "Texture.h"

#include <iostream>
#include <string>

Texture::Texture(): m_width(0), m_height(0), m_path(""), m_texture(NULL)
{
}

Texture::~Texture()
{
	if (m_texture != NULL)
	{
		std::cout << "Destroy Texture: " << m_path << std::endl;
		SDL_DestroyTexture(m_texture);
	}
}