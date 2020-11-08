#pragma once
#include "Brick.h"

class BrickNormal : public Brick
{
public:
	BrickNormal()
	{
		this->type = BRICK_NORMAL;
		animation_set = animationsSets->Get(type);
		ChangeAnimation(BRICK_STATIC);
	}
	~BrickNormal() {};
};

