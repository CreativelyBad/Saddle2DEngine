#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

#include "ECS.h"
#include "Components.h"

GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.AddEntity());

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags)
{
	// make sure SDL inits properly
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!..." << std::endl;

		// create window and check it's created
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		// create renderer and check it's created
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;

		// create game objects
		player = new GameObject("assets/player.png", 0, 0);
		enemy = new GameObject("assets/enemy.png", 50, 50);
		map = new Map();

		newPlayer.AddComponent<PositionComponent>();
		newPlayer.GetComponent<PositionComponent>().SetPosition(500, 500);
	}
	else
	{
		// running false if SDL doesn't init properly
		isRunning = false;
	}
}

void Game::HandleEvents()
{
	// create event
	SDL_Event event;
	SDL_PollEvent(&event);

	// switch depending on event
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{
	player->Update();
	enemy->Update();
	manager.Update();
	std::cout << newPlayer.GetComponent<PositionComponent>().GetX() << ", " <<
		newPlayer.GetComponent<PositionComponent>().GetY() << std::endl;
}

void Game::Render()
{
	// clear renderer buffer
	SDL_RenderClear(renderer);

	// <-- THIS IS WHERE WE ADD STUFF TO RENDER -->
	map->DrawMap();
	player->Render();
	enemy->Render();

	// show backbuffer
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	// get rid of everything
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}