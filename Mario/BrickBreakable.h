#pragma once
#include "Brick.h"
class BrickBreakable : public Brick
{
public:
	BrickBreakable();
	~BrickBreakable() {};
	void Update();
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

