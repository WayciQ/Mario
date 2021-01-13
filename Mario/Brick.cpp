#include "Brick.h"

Brick::Brick() {
	tag = GROUND;
	typeParent = BLOCK;
	isDead = false;
	SetBBox(UNIT_GAME, UNIT_GAME);
}
void Brick::Render()
{
	CurAnimation->Render(x, y);
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
	r = x + widthBBox;
	b = y + heightBBox;
}