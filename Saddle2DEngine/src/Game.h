#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

class Game
{
public:
	// constructor and deconstructor
	Game();
	~Game();

	// called on start
	void Init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags);

	// called during game loop
	void HandleEvents();
	void Update();
	void Render();

	// called on end
	void Clean();

	// return if game is running
	bool Running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
private:
	bool isRunning;
	SDL_Window* window;
};

