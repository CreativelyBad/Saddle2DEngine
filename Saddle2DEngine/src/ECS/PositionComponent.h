#pragma once

#include "Components.h"

class PositionComponent : public Component
{
private:
	int xpos;
	int ypos;

public:

	PositionComponent()
	{
		xpos = 0;
		ypos = 0;
	}

	PositionComponent(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

	int GetX() { return xpos; }
	void SetX(int x) { xpos = x; }
	int GetY() { return ypos; }
	void SetY(int y) { xpos = y; }
	void SetPosition(int x, int y) { xpos = x; ypos = y; }

	void Update() override
	{
		xpos++;
		ypos++;
	}
};