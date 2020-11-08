#include "BrickBreakable.h"

BrickBreakable::BrickBreakable()
{
	
	this->type = BRICK_BREAKABLE;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BRICK_BREAKABLE_STATIC);
}

void BrickBreakable::Update() 
{
	if (isDead)
	{
		canDel = true;
	}
}

