#include "Koomba.h"
#include "Mario.h"
#include "PlayerKickState.h"

#define KOOMBA_TIME_REVIVAL 10000
Koomba::Koomba(TYPE type) : Enemy(type)
{
	isDead = true;
	checkDead = false;
	isKicked = false;
	this->type = KOOMBA;
	//Revival();
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
			isDead = false;
			checkDead = false;
			Revival();
			TimeDead = 0;
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
						
						if(vx > 0 && !isDead )
							ChangeAnimation(KOOMBA_WALKING_RIGHT);
						else 
							ChangeAnimation(KOOMBA_WALKING_LEFT);
					}
				}

			}
			if (e->obj->tag == PLAYER)
			{
				
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
	ChangeAnimation(KOOMBA_WALKING_RIGHT);
	isKicked = false;
}

void Koomba::UpdatePosition(DWORD dt)
{
	int posX = player->nx > 0 ? player->x+13 : player->x -13;
	int	posY =  player->y + 5;
	vy = 0;
	SetPosition(posX, posY);
}