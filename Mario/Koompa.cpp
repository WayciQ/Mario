#include "Koompa.h"
#include "Mario.h"
#include "PlayerKickState.h"

Koompa::Koompa() : Enemy()
{
	Revival();
	typeParent = KOOMPA;
}
void Koompa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOMPA_BBOX_WIDTH;
	bottom = y + KOOMPA_BBOX_HEIGHT;
	if (isDead)
		bottom = y + KOOMPA_BBOX_HEIGHT_DIE;
}

void Koompa::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_WALKING_RIGHT:
		nx = 1;
		vx = KOOMPA_WALKING_SPEED;
		break;
	case ENEMY_WALKING_LEFT:
		nx = -1;
		vx = -KOOMPA_WALKING_SPEED;
		break;
	case ENEMY_DIE_STAND:
		vx = 0;
		break;
	case ENEMY_DIE_FLIP:
		vx = 0;
		break;
	default:
		break;
	}
}
void Koompa::UpdatePosition(DWORD dt)
{
	int posX, posY;
	switch (player->level)
	{
	case RACCOON:
		posX = player->nx > 0 ? player->x + 75 : player->x - 39;
		posY = player->y + 27;
		break;
	case SMALL:
		posX = player->nx > 0 ? player->x + 45 : player->x - 39;
		posY = player->y;
		break;
	case BIG:case FIRE:
		posX = player->nx > 0 ? player->x + 45 : player->x - 39;
		posY = player->y + 27;
		break;
	}
	vy = 0;
	SetPosition(posX, posY);
	
}
void Koompa::UpdateLocation()
{
	if (x > maxRight - widthBBox -  10) {
		SetState(ENEMY_WALKING_LEFT);
	}
	else if (x < maxLeft) {
		SetState(ENEMY_WALKING_RIGHT);
	}
		
}