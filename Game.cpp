#include "Game.h"
#include "Entity.h"
#include <iostream>

Entity entity;
int velX, velY;
double SPEED = 0.1;

Game::~Game()
{

}

void Game::init(const char* title, int posX, int posY, int screenWidth, int screenHeight, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Uint32 flags = fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
		window = SDL_CreateWindow(title, posX, posY, screenWidth, screenHeight, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (SDL_NumJoysticks() < 1)
		{
			SDL_Log("Warning: No joysticks connected!");
		}
		else
		{
			gameController = SDL_JoystickOpen(0);
			if (gameController == NULL)
			{
				SDL_Log("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

		if (renderer)
		{
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
			SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
		}

		TTF_Init();

		// TODO: test only - to be removed
		entity = Entity("assets/images/test_sprite.png", renderer);

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
	// SDL converts the stick position into a number between -32768 and 32767. 
	// This deadzone allows us to define a window we can ignore, thus avoiding
	// light taps on the stick.
	const int JOYSTICK_DEAD_ZONE = 8000;
	double currentX = 0.0;
	double currentY = 0.0;

	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		//case SDL_KEYDOWN:
		//	switch (event.key.keysym.scancode)
		//	{
		//		case SDL_SCANCODE_UP:
		//			currentY = entity.getY();
		//			entity.setY(currentY - SPEED);
		//			break;
		//		case SDL_SCANCODE_LEFT:
		//			currentX = entity.getX();
		//			entity.setX(currentX - SPEED);
		//			break;
		//		case SDL_SCANCODE_DOWN:
		//			currentY = entity.getY();
		//			entity.setY(currentY + SPEED);
		//			break;
		//		case SDL_SCANCODE_RIGHT:
		//			currentX = entity.getX();
		//			entity.setX(currentX + SPEED);
		//			break;
		//	}
		//	break;
		case SDL_JOYAXISMOTION:
			//Motion on controller 0
			if (event.jaxis.which == 0)
			{
				//X axis motion
				if (event.jaxis.axis == 0)
				{
					//Left of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						velX = -1;
					}
					//Right of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						velX = 1;
					}
					else
					{
						velX = 0;
					}
				}
				//Y axis motion
				else if (event.jaxis.axis == 1)
				{
					//Below of dead zone
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						velY = -1;
					}
					//Above of dead zone
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						velY = 1;
					}
					else
					{
						velY = 0;
					}
				}
			}
			break;
	}
}


void Game::update()
{

}

// TODO: use lag value to normalize rendering on the screen
void Game::render(double lag)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	entity.setX(entity.getX() + double(velX) * SPEED);
	entity.setY(entity.getY() + double(velY) * SPEED);
	entity.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_JoystickClose(gameController);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Game::running()
{
	return isRunning;
}