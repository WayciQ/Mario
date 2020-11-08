#include "Enemy.h"
void Enemy::Render()
{
	CurAnimation->Render(x, y, 255);
	//RenderBoundingBox();
}

void Enemy::ChangeAnimation(STATEOBJECT state)
{
	CurAnimation = animation_set->Get(state);
}