#include "Goomba.h"
#include "Camera.h"
#include "Mario.h"
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
void Goomba::UpdatePosition(DWORD dt)
{
	if ((x > camera->cam_x || x < camera->cam_x + camera->GetWidth()))
	{
		if ((x > player->x + DISTANCE_FL))
		{
			vx = -GOOMBA_WALKING_SPEED;
		}
		else if ((x < player->x - DISTANCE_FL)) {
			vx = GOOMBA_WALKING_SPEED;
		}
	}

	GameObject::Update(dt);
}
void Goomba::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
}