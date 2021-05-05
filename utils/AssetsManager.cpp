#include "AssetsManager.h"
#include <fstream>

SDL_Texture* AssetsManager::loadTexture(const char* filePath, SDL_Renderer* renderer)
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


void AssetsManager::displayText(const char* text, int size, SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", size);
	SDL_Color color = { 0, 0, 0 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };

	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(renderer);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}