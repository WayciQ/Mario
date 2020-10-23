#include "Brick.h"

Brick::Brick(STATEOBJECT types) {
	tag = GROUND;
	type = BRICK;
	this->typeBrick = types;
}
void Brick::Render()
{
	animation_set->Get(typeBrick)->Render(x, y);
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}