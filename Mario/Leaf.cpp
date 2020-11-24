#include "Leaf.h"
#define SPEED_X_LEAF 0.5f
#define SPEED_Y_LEAF 0.01f
Leaf::Leaf(float x, float y) :Item(x, y)
{
	type = LEAF;
	widthBBox = heightBBox = 16;
	CenX = x;
	CenY = y;
	CurAnimation = animationsSets->Get(LEAF)->Get(FIRE_FIRE_RIGHT);
	isFalling = false;
}
void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//x = startPositionX + 60cos(0.004 * dt)
	if (!isFalling)
	{
		y -= 4;
		if (y <= CenY - 48)
		{
			isFalling = true;
			x = CenX + 16;
			CenX = x;
			
		}
	}
	else
	{
		y += 0.09f;
		//x += sin(y);
		x = CenX + 20 * cos(y);
		if (x <= CenX-10)
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