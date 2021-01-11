#include "Brick.h"

Brick::Brick() {
	tag = GROUND;
	typeParent = BLOCK;
	isDead = false;
	SetBBox(16, 16);
}
void Brick::Render()
{
	CurAnimation->Render(x, y, 255);
	//RenderBoundingBox();
}
void Brick::ChangeAnimation(STATEOBJECT state)
{
	CurAnimation = animation_set->Get(state);
}
void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}