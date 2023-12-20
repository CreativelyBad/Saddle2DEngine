#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	// fps cap and delay
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// create game
	game = new Game();
	game->Init("Saddle Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	// game loop
	while (game->Running())
	{
		// get time time since SDL initialized
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		// get time to do previous tasks
		frameTime = SDL_GetTicks() - frameStart;

		// limit frames
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();

	return 0;
}