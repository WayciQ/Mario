#include "Enemy.h"
void Enemy::Render()
{
	CurAnimation->Render(x, y, 255);
	RenderBoundingBox();
}
