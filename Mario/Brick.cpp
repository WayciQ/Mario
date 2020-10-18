#include "Brick.h"

Brick::Brick() {
	tag = GROUND;
}
void Brick::Render()
{
	animation_set->Get(BRICK_NORMAL)->Render(x, y);
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}