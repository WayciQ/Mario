#include "Koomba.h"
#include "Mario.h"
#include "PlayerKickState.h"

#define KOOMBA_TIME_REVIVAL 7000
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
	vy += MARIO_GRAVITY * dt;

	if (isDead)
	{
		ChangeAnimation(KOOMBA_DIE);
	}


	if(checkDead)
	{
		if (GetTickCount() - TimeDead > KOOMBA_TIME_REVIVAL)
		{
			TimeDead = 0;
			Revival();
		}
	}
	
	
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (player->isHolding)
	{
		UpdatePosition(dt);
	}

	if (!player->canHolding)
	{
		if (player->isHolding)
		{
			player->ChangeAnimation(new PlayerKickState());
			isKicked = true;
			if (player->nx == 1)
			{
				vx = 2 * MARIO_WALKING_SPEED;
			}
			else {
				vx = -2 * MARIO_WALKING_SPEED;
			}
			player->isHolding = false;
		}
		
	}


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
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
		{
			
			
		}
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
						vx = -vx;
						if(!isDead)
						{
							if (vx > 0)
								ChangeAnimation(KOOMBA_WALKING_RIGHT);
							else
								ChangeAnimation(KOOMBA_WALKING_LEFT);
						}
					}
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
	vx = KOOMBA_WALKING_SPEED;
	isDead = false;
	checkDead = false;
	isKicked = false;
	isKicked = false;
	ChangeAnimation(KOOMBA_WALKING_RIGHT);
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