#include "BrickQuestion.h"
#define BRICK_DEFLECT_SPEED 0.03f
BrickQuestion::BrickQuestion(float CurY)
{
	isDead = false;
	curY = CurY;
	vy = -BRICK_DEFLECT_SPEED;
	this->type = BRICK_QUESTION;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BRICK_STATIC);
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
		
		ChangeAnimation(BRICK_HITTED);
		y += dy;
	}
	
}

