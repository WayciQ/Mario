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