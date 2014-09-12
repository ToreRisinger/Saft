#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include "Renderer.h"

Texture::Texture(std::string fileName)
{
	m_Texture = NULL;
	m_Width = 0;
	m_Height = 0;
	loadTexture(fileName);
}

Texture::~Texture()
{
	free();
}

void Texture::free()
{
	if (m_Texture != NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

bool Texture::loadTexture(std::string fileName)
{
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(("./res/textures/" + fileName).c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", ("./res/textures/" + fileName).c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer::gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", ("./res/textures/" + fileName).c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			m_Width = loadedSurface->w;
			m_Height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	m_Texture = newTexture;
	return m_Texture != NULL;
}

void Texture::render(int x, int y, int width, int height)
{
	SDL_Rect renderRect = { x, y, width, height };
	SDL_RenderCopy(Renderer::gRenderer, m_Texture, NULL, &renderRect);
}

int Texture::getHeight()
{
	return m_Height;
}

int Texture::getWidth()
{
	return m_Width;
}