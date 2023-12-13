#pragma once

#include "ECS.h"

class PositionComponent : public Component
{
private:
	int xpos;
	int ypos;

public:
	int GetX() { return xpos; }
	int GetY() { return ypos; }

	void Init() override
	{
		xpos = 0;
		ypos = 0;
	}

	void Update() override
	{
		xpos++;
		ypos++;
	}

	void SetPosition(int x, int y)
	{
		xpos = x;
		ypos = y;
	}
};