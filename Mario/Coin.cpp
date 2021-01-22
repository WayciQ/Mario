#include "Coin.h"
#include "Bricks.h"
#include "Grid.h"
#include "Effects.h"
#define COIN_JUMP 0.9f
#define TIME_BACK_TO_BLOCK 5000
#define TIME_DEL 600
Coin::Coin(float x, float y, STATEOBJECT state, bool isStatic) : Item(x, y)
{
	this->isStatic = isStatic;
	type = COIN;
	SetBBox(UNIT_GAME, UNIT_GAME);
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
		vy = -COIN_JUMP;
	}
	
}
void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;
	y += dy;
	if (isStatic) {
		vy = 0;
		if (GetTickCount() - time >= TIME_BACK_TO_BLOCK && !isKicked && isCoinChange)
		{
			auto Brick = Bricks::CreateBrick(BLOCK_BREAKABLE,0,COIN);
			grid->AddStaticObject(Brick,x,y);
			isKicked = true;
			isDead =true;
		}
	}
	else {
		if (GetTickCount() - time >= TIME_DEL)
		{
			auto ef = Effects::CreateEffect(SCORE_100);
			grid->AddMovingObject(ef, x, y);
			isDead = true;
		}
	}

	if (isDead)
	{
		vy = 0;
		canDel = true;
	}

}