#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

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
		map = new Map();

		// ecs implementation

		player.AddComponent<TransformComponent>(4);
		player.AddComponent<SpriteComponent>("assets/player.png");
		player.AddComponent<KeyboardController>();
		player.AddComponent<ColliderComponent>("player");

		wall.AddComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 4);
		wall.AddComponent<SpriteComponent>("assets/dirt.png");
		wall.AddComponent<ColliderComponent>("wall");

	}
	else
	{
		// running false if SDL doesn't init properly
		isRunning = false;
	}
}

void Game::HandleEvents()
{
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
	manager.Refresh();
	manager.Update();

	if (Collision::AABB(player.GetComponent<ColliderComponent>().collider,
						wall.GetComponent<ColliderComponent>().collider))
	{
		std::cout << "Wall Hit" << std::endl;
	}
}

void Game::Render()
{
	// clear renderer buffer
	SDL_RenderClear(renderer);

	// <-- THIS IS WHERE WE ADD STUFF TO RENDER -->
	map->DrawMap();
	manager.Draw();

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