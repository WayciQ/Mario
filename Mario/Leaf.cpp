#include "Leaf.h"
#define SPEED_X_LEAF 0.5f
#define SPEED_Y_LEAF 0.09f
#define LEAF_MOVE 45
#define Y_SPAW_UP CenY - 144
#define X_SPAW_UP CenX + 32
Leaf::Leaf(float x, float y) :Item(x, y)
{
	tag = ITEM;
	type = LEAF;
	SetBBox(0, 0);
	CenX = x;
	CenY = y;
	CurAnimation = animationsSets->Get(LEAF)->Get(WEAPON_SHOOT_RIGHT);
	isFalling = false;
}
void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	
	//x = startPositionX + 60cos(0.004 * dt)
	if (!isFalling)
	{
		
		y += dy;
		vy = -MARIO_JUMP_SPEED_Y;
		if (y <= Y_SPAW_UP)
		{
			isFalling = true;
			x = X_SPAW_UP;
			CenX = x;
			vy = 0;
			
		}
	}
	else
	{
		SetBBox(UNIT_GAME, UNIT_GAME);
		y += SPEED_Y_LEAF;
		//x += sin(y);
		x = CenX + LEAF_MOVE * cos(y);
		if (x <= X_SPAW_UP)
		{
			CurAnimation = animationsSets->Get(LEAF)->Get(WEAPON_SHOOT_LEFT);
		}
		else if(x > CenX)
		{
			CurAnimation = animationsSets->Get(LEAF)->Get(WEAPON_SHOOT_RIGHT);
		}
	}
	
	if (isDead)
		canDel = true;
}

void Leaf::UpdatePosition(DWORD dt)
{
	
}