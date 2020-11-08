#include "Brick.h"

Brick::Brick() {
	tag = GROUND;
	isDead = false;
}
void Brick::Render()
{
	CurAnimation->Render(x, y, 255);
	RenderBoundingBox();
}
void Brick::ChangeAnimation(STATEOBJECT state)
{
	CurAnimation = animation_set->Get(state);
}
void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}