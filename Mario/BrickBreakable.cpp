#include "BrickBreakable.h"
#include "BreakBrick.h"
#include "Items.h"
#include "Grid.h"
#include "Effects.h"
#define SPEED_Y_1	0.6
#define SPEED_Y_2	0.6
#define LOCA_X_BREAK x + 24
#define X_UP_HIT	curY - 24
#define X_RESPANW_ITEM	y - 48
BrickBreakable::BrickBreakable(int curY,TYPE child,int Num)
{
	SetBBox(UNIT_GAME, UNIT_GAME);
	if (child == COIN)
	{
		NumberHit = 1;
		canBreak = true;
		isKicked = false;
		isSpawnItem = false;
	}
	else if (child == BRICKBREAK_10_TIME) {
		NumberHit = Num;
		canBreak = false;
		isSpawnItem = true;
	}
	else{
		NumberHit = Num;
		canBreak = false;
		isSpawnItem = false;
	}


	this->child = child;
	this->type = BLOCK_BREAKABLE;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	isDone = false;
	this->curY = curY;
}

void BrickBreakable::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDead)
	{
		if (canBreak)
		{
			if (isKicked)
			{
				auto item = Items::CreateItem(COIN, x, y, true, BLOCK_HITTED);
				grid->AddStaticObject(item, x, y);
				isKicked = false;
			}
			else
			{
				BreakBrick* brick = new BreakBrick(1, -SPEED_Y_1);
				grid->AddStaticObject(brick, x, y);
				brick = new BreakBrick(1, -SPEED_Y_2);
				grid->AddStaticObject(brick, x, y);
				brick = new BreakBrick(-1, -SPEED_Y_2);
				grid->AddStaticObject(brick, x, y);
				brick = new BreakBrick(-1, -SPEED_Y_1);
				grid->AddStaticObject(brick, LOCA_X_BREAK, y);
			}
			canDel = true;
		}
		else {
			if (NumberHit >= 1) {
				if (!isDone) {
					y -= BRICK_DEFLECT_SPEED;
					if (y <= X_UP_HIT) {
						auto ef = Effects::CreateEffect(SCORE_100);
						grid->AddMovingObject(ef, x, y);
						isDone = true;
					}
				}
				else {
					y += BRICK_DEFLECT_SPEED;
				}
			}
			if (y >= curY) {
				
				y = curY;
				if (NumberHit >= 1) {
					isDone = false;
					isDead = false;
					NumberHit--;
				}
			}
			if (NumberHit < 1) {
				ChangeAnimation(BLOCK_HITTED);
				if (!isSpawnItem)
				{
					if (child == BUTTON) {
						auto item = Items::CreateItem(child, x, X_RESPANW_ITEM, false);
						grid->AddStaticObject(item, x, X_RESPANW_ITEM);
					}
					else {
						auto item = Items::CreateItem(child, x, y, false);
						grid->AddStaticObject(item, x, y);
					}
					isSpawnItem = true;
				}
			}
		}
	}
	
}

