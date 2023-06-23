#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	// increment pos
	xpos++;
	ypos++;

	// set src rect
	srcRect.h = 16;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;

	// set dest rect and upscale size
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 4;
	destRect.h = srcRect.h * 4;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}