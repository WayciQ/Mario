#include "BrickBreakable.h"
#include "BreakBrick.h"
BrickBreakable::BrickBreakable()
{
	
	this->type = BLOCK_BREAKABLE;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	
}

void BrickBreakable::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDead)
	{
		
		canDel = true;

	}
}

