#include "BrickQuestion.h"
#include "Items.h"
#include "Grid.h"

BrickQuestion::BrickQuestion(float CurY,TYPE Child)
{
	isDead = false;
	isSpawnItem = false;
	this->child = Child;
	this->tag = GROUND;
	this->type = BLOCK_QUESTION;
	curY = CurY;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	SetBBox(UNIT_GAME, UNIT_GAME);
	isDone = false;
}
void BrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//GameObject::Update(dt);
	
	
	if(isDead)
	{
		ChangeAnimation(BLOCK_HITTED);
		if (!isDone) {
			y -= BRICK_DEFLECT_SPEED;
			if (y <= curY - 24) {
				isDone = true;
			}
		}
		else {
			y += BRICK_DEFLECT_SPEED;
		}

		if (!isSpawnItem && child == COIN) {
			auto item = Items::CreateItem(child, x, y, false);
			grid->AddMovingObject(item);
			isSpawnItem = true;
		}
		if (y >= curY) {
			y = curY;
			if (!isSpawnItem && child != COIN) {
				auto item = Items::CreateItem(child, x, y, false);
				grid->AddMovingObject(item);
				isSpawnItem = true;
			}
		}
	}

	

}

