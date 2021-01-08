#include "BrickBreakable.h"
#include "BreakBrick.h"
#include "Items.h"
#include "Grid.h"
BrickBreakable::BrickBreakable(int curY,TYPE child,int Num)
{
	SetBBox(BBOX_16, BBOX_16);
	if (child == COIN)
	{
		NumberHit = 1;
		canBreak = true;
		isKicked = false;
	}
	else {
		NumberHit = Num;
		canBreak = false;
	}
	
	this->child = child;
	this->type = BLOCK_BREAKABLE;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	isSpawnItem = false;
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
				BreakBrick* brick = new BreakBrick(1, -0.2f);
				grid->AddStaticObject(brick, x, y);
				brick = new BreakBrick(1, -0.3f);
				grid->AddStaticObject(brick, x, y);
				brick = new BreakBrick(-1, -0.2f);
				grid->AddStaticObject(brick, x, y);
				brick = new BreakBrick(-1, -0.3f);
				grid->AddStaticObject(brick, x + 8, y);
			}
			canDel = true;
		}
		else {
			if (NumberHit >= 1) {
				if (!isDone) {
					y -= 1;
					if (y <= curY - 8) {
						isDone = true;
					}
				}
				else {
					y += 1;
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
						auto item = Items::CreateItem(child, x, y - 16, false);
						grid->AddStaticObject(item, x, y - 16);
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

