#include "SwitchBlock.h"
#include "Grid.h"
SwitchBlock::SwitchBlock(float x,float y):Item(x, y)
{
	this->type = BUTTON;
	widthBBox = heightBBox = 16;
	CurAnimation = animationsSets->Get(BUTTON)->Get(BLOCK_STATIC);
	isChange = false;
}
void SwitchBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> ChangeCoin;
	ChangeCoin.clear();
	
	if (isDead && !isChange)
	{
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
	right = x + widthBBox;
	bottom = y + heightBBox;
	if (isDead) {
		top = y + heightBBox;
		heightBBox = 9;
	}
}