#pragma once
#include "Brick.h"

class BrickNormal : public Brick
{
public:
	BrickNormal()
	{
		this->type = BLOCK_NORMAL;
		animation_set = animationsSets->Get(type);
		ChangeAnimation(BLOCK_STATIC);
	}
	~BrickNormal() {};
};

