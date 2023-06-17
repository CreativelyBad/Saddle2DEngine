#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* _renderer, int x, int y)
{
	renderer = _renderer;
	objTexture = TextureManager::LoadTexture(texturesheet, _renderer);

	xpos = x;
	ypos = y;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	xpos++;
	ypos++;

	srcRect.h = 16;
	srcRect.w = 16;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 4;
	destRect.h = srcRect.h * 4;
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}