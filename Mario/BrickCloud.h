#pragma once
#include "Brick.h"
class BrickCloud : public Brick
{
public:
	BrickCloud() : Brick()
	{
		this->type = BLOCK_CLOUD;
		animation_set = animationsSets->Get(type);
		ChangeAnimation(BLOCK_STATIC);
	}
	~BrickCloud() {};
};

