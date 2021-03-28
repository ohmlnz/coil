#pragma once

#include "SDL.h"
#include "SDL_image.h"


class AssetsManager
{
public:
	static SDL_Texture* LoadTexture(const char* filePath, SDL_Renderer* renderer);
};