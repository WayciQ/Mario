#include "BrickQuestion.h"
#include "Items.h"
#include "Grid.h"
#define BRICK_DEFLECT_SPEED 0.05f
BrickQuestion::BrickQuestion(float CurY,TYPE Child)
{
	isDead = false;
	isSpawnItem = false;
	this->child = Child;
	this->type = BLOCK_QUESTION;
	curY = CurY;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	
	isDone = false;
}
void BrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(isDead)
	{
		ChangeAnimation(BLOCK_HITTED);
		
		if (!isSpawnItem) {

			auto item = Items::CreateItem(child, x, y, false);
			grid->AddMovingObject(item);
			isSpawnItem = true;
		}
	}
	

}

