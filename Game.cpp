#include "Game.h"

Game::~Game() {}

void Game::init(const char* title, int posX, int posY, int screenWidth, int screenHeight, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Uint32 flags = fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
		_window = SDL_CreateWindow(title, posX, posY, screenWidth, screenHeight, flags);
		_renderer = SDL_CreateRenderer(_window, -1, 0);

		// TODO: decouple into its own class
		if (SDL_NumJoysticks() < 1)
		{
			SDL_Log("Warning: No joysticks connected!");
		}
		else
		{
			_gameController = SDL_JoystickOpen(0);
			if (_gameController == NULL)
			{
				SDL_Log("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

		if (_renderer)
		{
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
			SDL_RenderSetLogicalSize(_renderer, 480, 270);
		}

		TTF_Init();
		_world = new World(_renderer);
		_isRunning = true;
	}
	else
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		_isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_PollEvent(&_event);

	switch (_event.type)
	{
		case SDL_QUIT:
			_isRunning = false;
			break;
		// ... add other high level events here
	}

	_world->events(&_event);
}


void Game::update()
{
	_world->update();
}

// TODO: use lag value to normalize rendering on the screen
void Game::render(double lag)
{
	SDL_RenderClear(_renderer);
	_world->render(lag);
	SDL_RenderPresent(_renderer);
}

void Game::clean()
{
	SDL_JoystickClose(_gameController);
	TTF_Quit();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Game::running()
{
	return _isRunning;
}