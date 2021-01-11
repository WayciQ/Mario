#include "Leaf.h"
#define SPEED_X_LEAF 0.5f
#define SPEED_Y_LEAF 0.09f
#define LEAF_MOVE 15

Leaf::Leaf(float x, float y) :Item(x, y)
{
	tag = ITEM;
	type = LEAF;
	SetBBox(16, 16);
	CenX = x;
	CenY = y;
	CurAnimation = animationsSets->Get(LEAF)->Get(FIRE_FIRE_RIGHT);
	isFalling = false;
}
void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	
	//x = startPositionX + 60cos(0.004 * dt)
	if (!isFalling)
	{
		y += dy;
		vy = -0.2f;
		if (y <= CenY - 48)
		{
			isFalling = true;
			x = CenX + 16;
			CenX = x;
			vy = 0;
			
		}
	}
	else
	{
		y += SPEED_Y_LEAF;
		//x += sin(y);
		x = CenX + LEAF_MOVE * cos(y);
		if (x <= CenX - 10)
		{
			CurAnimation = animationsSets->Get(LEAF)->Get(FIRE_FIRE_LEFT);
		}
		else if(x > CenX)
		{
			CurAnimation = animationsSets->Get(LEAF)->Get(FIRE_FIRE_RIGHT);
		}
	}
	
	if (isDead)
		canDel = true;
}

void Leaf::UpdatePosition(DWORD dt)
{
	
}