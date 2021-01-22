#include "Enemy.h"
void Enemy::Render()
{
	ChangeAnimation();
	CurAnimation->Render(x, y);
	//RenderBoundingBox();
}

void Enemy::ChangeAnimation()
{
	CurAnimation = animation_set->Get(state);
}
