#include "Goomba.h"


Goomba::Goomba() : Enemy()
{
	typeParent = GOOMBA;
	widthBBox = GOOMBA_BBOX_WIDTH;
	heightBBox = GOOMBA_BBOX_HEIGHT;
}
void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + widthBBox;
	bottom = y + heightBBox;
	if(isDead)
		heightBBox = GOOMBA_BBOX_HEIGHT_DIE;
}

void Goomba::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
}