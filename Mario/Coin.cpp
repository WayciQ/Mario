#include "Coin.h"
Coin::Coin(float x, float y, bool isStatic) : Item(x, y)
{
	this->isStatic = isStatic;
	type = COIN;
	widthBBox = heightBBox = 16;
	CurAnimation = animationsSets->Get(COIN)->Get(BLOCK_STATIC);
	vy = -0.2f;
	time = GetTickCount();

}
void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;
	y += dy;
	if (isStatic) {
		vy = 0;
	}
	else {
		if (GetTickCount() - time >= 400)
		{
			isDead = true;
		}
	}

	if (isDead)
	{
		vy = 0;
		canDel = true;
	}

}