#include "GraphicsManager.h"

#include <iostream>
#include <assert.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

GraphicsManager::GraphicsManager(Window const& window)
{
	std::cout << "Create Renderer" << std::endl;
	m_renderer = SDL_CreateRenderer(window.m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL)
	{
		throw std::runtime_error("Failed to create Renderer");
	}
}

GraphicsManager::~GraphicsManager()
{
	std::cout << "Destroy Renderer" << std::endl;
	SDL_DestroyRenderer(m_renderer);
}

void GraphicsManager::loadTexture(std::string path, Texture & texture) const
{
	assert(texture.m_texture == NULL);

	SDL_Surface * tmpSurface = IMG_Load(path.c_str());

	if (tmpSurface != NULL)
	{
		texture.m_width = tmpSurface->w;
		texture.m_height = tmpSurface->h;
		texture.m_path = path;
		
		std::cout << "Create Texture: " << path << std::endl;
		texture.m_texture = SDL_CreateTextureFromSurface(m_renderer, tmpSurface);
		if (texture.m_texture == NULL)
		{
			SDL_FreeSurface(tmpSurface);
			throw std::runtime_error("Failed to load texture");
		}

		SDL_FreeSurface(tmpSurface);
	}
	else
	{
		throw std::runtime_error("Failed to load image");
	}
}

void GraphicsManager::drawTexture(Texture const& texture, Vector2 position, float scale) const
{
	assert(texture.m_texture != NULL);

	SDL_Rect destRect = {
		position.x,
		position.y,
		int(texture.m_width * scale),
		int(texture.m_height * scale)
	};

	SDL_RenderCopy(m_renderer, texture.m_texture, NULL, &destRect);
}

void GraphicsManager::render() const
{
	SDL_RenderPresent(m_renderer);
}

void GraphicsManager::clearScreen() const
{
	SDL_RenderClear(m_renderer);
}
