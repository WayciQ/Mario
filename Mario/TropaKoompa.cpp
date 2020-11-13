#include "TropaKoompa.h"
#include "Mario.h"
#include "PlayerKickState.h"
TropaKoompa::TropaKoompa() : Koompa()
{
	this->type = TROPA_KOOMPA;
	jumped = false;
	nx = 1;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_WALKING_LEFT);
}
void TropaKoompa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;

	

	if (isDead)
	{
		if (canRespawn)
		{
			if (!jumped && !isFlip)
			{
				jumped = true;
				Revival();
				return;
			}
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
			if  (GetTickCount() - TimeDead > KOOMPA_TIME_REVIVAL)
			{
				player->canHolding = false;
				player->isHolding = false;
				TimeDead = 0;
				Revival();
			}
			
		}
		else {
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
	else
	{
		if (jumped)
		{
			if (nx > 0)
				state = ENEMY_WALKING_RIGHT;
			else state = ENEMY_WALKING_LEFT;
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
		y += min_ty * dy + ny * 0.04f;

		if (ny == -1) {
			if (!jumped && !isFlip)
				vy = -0.25f;
			else vy = 0;
		};
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
						this->nx = -this->nx;
						if (!isDead && jumped)
						{
							if (this->nx < 0)
								state = ENEMY_WALKING_LEFT;
							else
								state = ENEMY_WALKING_RIGHT;
						}
						else if (!isDead && !jumped)
						{
							if (this->nx > 0)
								state = ENEMY_JUMPING_LEFT;
							else
								state = ENEMY_JUMPING_RIGHT;
						}
						vx = -vx;
					}
					if (e->ny == 1)
					{
						vy = 0;
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

void TropaKoompa::SetState(STATEOBJECT state)
{
	Koompa::SetState(state);
	switch (state)
	{
	case ENEMY_JUMPING_RIGHT:case ENEMY_WALKING_RIGHT:
		vx = KOOMBA_WALKING_SPEED;
		break;
	case ENEMY_JUMPING_LEFT: case ENEMY_WALKING_LEFT:
		vx = -KOOMBA_WALKING_SPEED;
		break;
	}
}
void TropaKoompa::Revival()
{
	y -= 9;
	nx = 1;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	jumped = true;
	SetState(ENEMY_WALKING_RIGHT);
}