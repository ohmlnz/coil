#include "Game.h"

int main(int argc, char *argv[])
{
	const int screenWidth = 640;
	const int screenHeight = 480;
	const int MS_PER_UPDATE = 16;
	Uint32 previous = SDL_GetTicks();
	double lag = 0.0;

	Game game;

	game.init("Coil", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenHeight, screenHeight, false);

	while (game.running())
	{
		Uint32 current = SDL_GetTicks();
		Uint32 elapsed = current - previous;
		previous = current;
		lag += elapsed;
		game.handleEvents();

		while (lag >= MS_PER_UPDATE)
		{
			game.update();
			lag -= MS_PER_UPDATE;
		}

		game.render(double(lag / MS_PER_UPDATE));
	}

	game.clean();

	return 0;
}