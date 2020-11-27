#include "Coin.h"
#include "Bricks.h"
#include "Grid.h"
Coin::Coin(float x, float y, STATEOBJECT state, bool isStatic) : Item(x, y)
{
	this->isStatic = isStatic;
	type = COIN;
	widthBBox = heightBBox = 16;
	CurAnimation = animationsSets->Get(COIN)->Get(state);
	
	time = GetTickCount();
	isKicked = false;
	if (isStatic)
	{
		if(state == BLOCK_HITTED)
			isCoinChange = true;
	}
	else
	{
		isCoinChange = true;
		vy = -0.3f;
	}
	
}
void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;
	y += dy;
	if (isStatic) {
		vy = 0;
		if (GetTickCount() - time >= 5000 && !isKicked && isCoinChange)
		{
			auto Brick = Bricks::CreateBrick(BLOCK_BREAKABLE,0,COIN);
			grid->AddStaticObject(Brick,x,y);
			isKicked = true;
			isDead =true;
		}
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