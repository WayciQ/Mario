#include "BrickQuestion.h"
#include "Items.h"
#include "Grid.h"
#define BRICK_DEFLECT_SPEED 0.05f
BrickQuestion::BrickQuestion(float CurY,TYPE Child)
{
	isDead = false;
	curY = CurY;
	isSpawnItem = false;
	this->child = Child;
	vy = -BRICK_DEFLECT_SPEED;
	this->type = BLOCK_QUESTION;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
}
void BrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{
	GameObject::Update(dt);
	if (y > curY)
	{
		vy = 0;
		y = curY;
	}
	if (y < curY - 1)
	{
		vy = BRICK_DEFLECT_SPEED;
	}
	if(isDead)
	{
		
		ChangeAnimation(BLOCK_HITTED);
		if (!isSpawnItem) {

			auto item = Items::CreateItem(child, x, y - 16, false);
			grid->AddObjectToCell(item);
			isSpawnItem = true;
		}
		y += dy;
	}
	
}

