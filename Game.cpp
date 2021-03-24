#include "Game.h"

Game::~Game()
{

}

void Game::init(const char* title, int posX, int posY, int screenWidth, int screenHeight, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Uint32 flags = fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE;
		window = SDL_CreateWindow(title, posX, posY, screenWidth, screenHeight, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
			SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		TTF_Init();

		isRunning = true;
	}
	else
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT)
	{
		isRunning = false;
		return;
	}
}


void Game::update()
{

}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::running()
{
	return isRunning;
}