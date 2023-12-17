#pragma once

#include "Components.h"
#include "SDL.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* texturePath)
	{
		SetTexture(texturePath);
	}

	void SetTexture(const char* texturePath)
	{
		texture = TextureManager::LoadTexture(texturePath);
	}

	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 16;
		destRect.w = destRect.h = srcRect.w * 4;
	}

	void Update() override
	{
		destRect.x = (int)transform->position.x;
		destRect.y = (int)transform->position.y;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect);
	}
};
