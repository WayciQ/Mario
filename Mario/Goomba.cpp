#include "Goomba.h"


Goomba::Goomba() : Enemy()
{
	typeParent = GOOMBA;
}
void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;
	bottom = y + GOOMBA_BBOX_HEIGHT;
	if(isDead)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
}

void Goomba::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
}