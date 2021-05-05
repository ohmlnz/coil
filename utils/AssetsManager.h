#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class AssetsManager
{
public:
	static SDL_Texture* loadTexture(const char* filePath, SDL_Renderer* renderer);
	static void displayText(const char* text, int size, SDL_Renderer* renderer);
};