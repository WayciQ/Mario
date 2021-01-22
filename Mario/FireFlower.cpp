#include "FireFlower.h"
#define SPEED_UP 0.15f
#define SPEED_SPAWN 0.9
#define Y_SPANW_UP posY - 48
FireFlower::FireFlower(float x, float y) : Item(x, y)
{
	this->type = FIRE_FLOWER;
	isRespawn = true;
	SetBBox(UNIT_GAME, UNIT_GAME);
	SetPosition(x, y);
	CurAnimation = animationsSets->Get(FIRE_FLOWER)->Get(BLOCK_STATIC);
	posY = y;
}

void FireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isRespawn)
	{
		y -= SPEED_SPAWN;
		if (y <= Y_SPANW_UP)
		{
			isRespawn = false;
		}
	}
	if (isDead)
		canDel = true;
}
