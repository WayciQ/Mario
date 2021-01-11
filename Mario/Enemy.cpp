#include "Enemy.h"
void Enemy::Render()
{
	ChangeAnimation();
	CurAnimation->Render(x, y, 255);
	//RenderBoundingBox();
}

void Enemy::ChangeAnimation()
{
	CurAnimation = animation_set->Get(state);
}
