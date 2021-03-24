#include "Game.h"

int main(int argc, char *argv[])
{
	const int screenWidth = 640;
	const int screenHeight = 480;

	Game game;

	game.init("Coil", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenHeight, screenHeight, false);

	while (game.running())
	{
		game.handleEvents();
		game.update();
		game.render();
	}

	game.clean();

	return 0;
}