#include "ParaKoomba.h"
#include "Mario.h"
#include "PlayerKickState.h"
ParaKoompa::ParaKoompa() : Koompa()
{
	this->type = PARA_KOOMPA;
	Revival();
}
void ParaKoompa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;
	

	if (isDead)
	{
		if (canRespawn)
		{
			if (GetTickCount() - TimeDead > KOOMPA_TIME_REVIVAL - 1000)
			{

				if (!isFlip)
				{
					state = KOOMPA_RESPAWN;
				}
				else
				{
					state = KOOMPA_RESPAWN_FLIP;
				}
			}
			if (GetTickCount() - TimeDead > KOOMPA_TIME_REVIVAL)
			{
				player->canHolding = false;
				player->isHolding = false;
				TimeDead = 0;
				Revival();
			}
		}
		else{
			if (isKicked)
			{
				if (!isFlip)
				{
					state = KOOMPA_KICKED;
				}
				else
				{
					state = KOOMPA_KICKED_FLIP;
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
				canRespawn = false;
				if (player->nx == 1)
				{
					this->vx = 2 * MARIO_WALKING_SPEED;
				}
				else {
					this->vx = -2 * MARIO_WALKING_SPEED;
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
						if (!isDead)
						{
							this->nx = -this->nx;
							if (this->nx < 0)
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
				if (e->obj->tagChange == WEAPON && e->obj->isKicked)
				{
					startTimeDead();
					isFlip = true;
					vy = -0.2f;
					vx = 0;
					SetState(ENEMY_DIE_FLIP);
				}
				if (e->nx != 0)
				{
					x += dx;
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

void ParaKoompa::SetState(STATEOBJECT state)
{
	Koompa::SetState(state);
	switch (state)
	{
	case ENEMY_WALKING_RIGHT:
		vx = KOOMBA_WALKING_SPEED;
		break;
	case ENEMY_WALKING_LEFT:
		vx = -KOOMBA_WALKING_SPEED;
		break;
	}
}
void ParaKoompa::Revival()
{
	nx = 1;
	y -= 9;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_WALKING_RIGHT);
}