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
	right = x + KOOMBA_BBOX_WIDTH;
	bottom = y + KOOMBA_BBOX_HEIGHT;
	if (isDead)
		bottom = y + KOOMBA_BBOX_HEIGHT_DIE;
}

void Koompa::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_WALKING_RIGHT:
		vx = KOOMBA_WALKING_SPEED;
		break;
	case ENEMY_WALKING_LEFT:
		vx = -KOOMBA_WALKING_SPEED;
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
		posX = player->nx > 0 ? player->x + 25 : player->x - 13;
		posY = player->y + 9;
		break;
	case SMALL:
		posX = player->nx > 0 ? player->x + 15 : player->x - 13;
		posY = player->y;
		break;
	case BIG:case FIRE:
		posX = player->nx > 0 ? player->x + 15 : player->x - 13;
		posY = player->y + 9;
		break;
	}
	vy = 0;
	SetPosition(posX, posY);
}