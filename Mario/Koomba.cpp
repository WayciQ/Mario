#include "Koomba.h"
#include "Mario.h"
#include "PlayerKickState.h"

#define KOOMBA_TIME_REVIVAL 5000
Koomba::Koomba(TYPE type) : Enemy(type)
{
	this->type = KOOMBA;
	Revival();
}
Koomba::~Koomba() {}
void Koomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOMBA_BBOX_WIDTH;
	bottom = y + KOOMBA_BBOX_HEIGHT;
	if (isDead)
		bottom = y + KOOMBA_BBOX_HEIGHT_DIE;
}

void Koomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;
	if(canRespawn)
	{
		if (GetTickCount() - TimeDead > KOOMBA_TIME_REVIVAL - 1000)
		{
			
			if (!isFlip)
			{
				state = KOOMBA_RESPAWN;
			}
			else
			{
				state = KOOMBA_RESPAWN_FLIP;
			}
		}
		if (GetTickCount() - TimeDead > KOOMBA_TIME_REVIVAL)
		{
			player->canHolding = false;
			player->isHolding = false;
			TimeDead = 0;
			Revival();
		}
	}
	
	if (isDead)
	{
		if (!canRespawn) {
			if (isKicked)
			{
				if (!isFlip)
				{
					state = KOOMBA_KICKED;
				}
				else
				{
					state = KOOMBA_KICKED_FLIP;
				}
			}
			else {
				if (!isFlip)
				{
					state = ENEMY_DIE_STAND;
				}
				else
				{
					state = ENEMY_DIE_FLIP;
				}

			}
		}

		if (player->isHolding)
		{
			UpdatePosition(dt);
		}

		if (!player->canHolding)
		{
			if (player->isHolding)
			{
				player->ChangeAnimation(new PlayerKickState());
				this->isKicked = true;
				if (player->nx == 1)
				{
					this->vx = 2 * MARIO_WALKING_SPEED;
				}
				else {
					this->vx = - 2 * MARIO_WALKING_SPEED;
				}
				player->isHolding = false;
			}

		}
	}

	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		// block 
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.00004f;

		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->tag == GROUND)
			{
				if (e->obj->type == BOX_GROUND)
				{
					if (e->nx != 0)
					{
						x += dx;
					}
				}
				else
				{
					if (e->nx != 0)
					{
						if(!isDead)
						{
							if (vx > 0)
								state = ENEMY_WALKING_LEFT;
							else
								state = ENEMY_WALKING_RIGHT;
						}
						
						vx = -vx;
					}
				}

			}
			if (e->obj->tag == ENEMY)
			{

				if (e->nx != 0)
				{
					if (e->obj->type == KOOMBA && e->obj->isDead && e->obj->isKicked)
					{
						startTimeDead();
					}
					else {
						x += dx;
					}
				}
				if (e->ny != 0)
				{
					y += dy;
				}

			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Koomba::Revival()
{
	nx = 1;
	y -= 9;
	isDead = false;
	
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_WALKING_RIGHT);
}

void Koomba::SetState(STATEOBJECT state)
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
void Koomba::UpdatePosition(DWORD dt)
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