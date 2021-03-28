#include "AssetsManager.h"

SDL_Texture* AssetsManager::LoadTexture(const char* filePath, SDL_Renderer* renderer)
{
	SDL_Texture* texture;
	SDL_Surface* tempSurface = IMG_Load(filePath);

	if (!tempSurface)
	{
		SDL_Log("IMG_Load: %s\n", IMG_GetError());
		return nullptr;
	}

	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return texture;
}
