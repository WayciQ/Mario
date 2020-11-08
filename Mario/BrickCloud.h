#pragma once
#include "Brick.h"
class BrickCloud : public Brick
{
public:
	BrickCloud() : Brick()
	{
		
		this->type = BRICK_CLOUD;
		animation_set = animationsSets->Get(type);
		ChangeAnimation(BRICK_STATIC);
	}
	~BrickCloud() {};
};

