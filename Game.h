#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "World.h"

class Game
{
public:
	~Game();
	void init(const char* title, int posX, int posY, int screenWidth, int screenHeight, bool fullScreen);
	void handleEvents();
	void update();
	void render(double lag);
	void clean();
	bool running();
private:
	bool _isRunning;
	World* _world;
	SDL_Joystick* _gameController;
	SDL_Event _event;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};