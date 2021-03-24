#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Game
{
public:
	~Game();
	void init(const char* title, int posX, int posY, int screenWidth, int screenHeight, bool fullScreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
private:
	bool isRunning;
	SDL_Event event;
	SDL_Window* window;
	SDL_Renderer* renderer;
};