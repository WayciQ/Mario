#include "BrickBreakable.h"
#include "BreakBrick.h"
#include "Items.h"
#include "Grid.h"
BrickBreakable::BrickBreakable(TYPE child)
{
	SetBBox(16, 16);
	if (child == COIN)
	{
		canBreak = true;
		isKicked = false;
	}
	else
		canBreak = false;
	this->child = child;
	this->type = BLOCK_BREAKABLE;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	isSpawnItem = false;
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
			ChangeAnimation(BLOCK_HITTED);
			if (!isSpawnItem)
			{
				if (child == BUTTON) {
					auto item = Items::CreateItem(child, x, y - 16, false);
					grid->AddStaticObject(item, x, y - 16);
				}
				else {
					auto item = Items::CreateItem(child, x, y, false);
					grid->AddStaticObject(item,x, y);
				}
				isSpawnItem = true;
			}
		}
	}

}

