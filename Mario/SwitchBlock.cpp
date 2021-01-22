#include "SwitchBlock.h"
#include "Grid.h"
#include "Mario.h"
#define X_DIE 38
SwitchBlock::SwitchBlock(float x, float y) : Item(x,y)
{
	this->type = BUTTON;
	SetBBox(UNIT_GAME, UNIT_GAME);
	animation_set = animationsSets->Get(BUTTON);
	CurAnimation = animation_set->Get(BLOCK_STATIC);
	isChange = false;
}
void SwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> ChangeCoin;
	ChangeCoin.clear();
	
	if (isDead && !isChange)
	{
		SetBBox(UNIT_GAME, 0);
		player->vy = -MARIO_JUMP_DEFLECT_SPEED;
		CurAnimation = animationsSets->Get(BUTTON)->Get(BLOCK_HITTED);
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type == BLOCK_BREAKABLE && coObjects->at(i)->child == COIN)
			{
				coObjects->at(i)->isDead = true;
				coObjects->at(i)->isKicked = true;
			}
		}
		isChange = true;
	}
	
}
void SwitchBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	
	left = x;
	top = y;
	if (isDead) {
		top += X_DIE;
	}
	
	right = left + widthBBox;
	bottom = top + heightBBox;
	
}