#include "Goomba.h"
#include "Camera.h"
#include "Mario.h"
Goomba::Goomba() : Enemy()
{
	typeParent = GOOMBA; 
	SetBBox(GOOMBA_BBOX_WIDTH, GOOMBA_BBOX_HEIGHT);
	tagChange = ENEMY;
	tag = ENEMY;
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

}
void Goomba::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
}