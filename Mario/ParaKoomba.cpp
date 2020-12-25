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
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		// block 
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.004f;

		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->tag == GROUND) {
				if (e->ny == -1) {
					maxLeft = e->obj->x;
					maxRight = e->obj->x + e->obj->widthBBox - widthBBox;
				}
				if (e->obj->type == GROUND_BOX)
				{
					
					if (e->nx != 0)
					{
						x += dx;
					}
				}
				else if ((e->obj->type == BLOCK_QUESTION || e->obj->type == BLOCK_BREAKABLE) && isDead)
				{
					if (e->nx != 0) {
						e->obj->startTimeDead();
						vx = -vx;
					}
				}
				else
				{
					if (e->nx != 0)
					{
						if (!isDead)
						{
							this->nx = -this->nx;
							if (this->nx > 0) {
								SetState(ENEMY_WALKING_RIGHT);
							}
							else {
								SetState(ENEMY_WALKING_LEFT);
							}
						}
						else vx = -vx;
					}
				}

			}
			else
			{
				if (e->obj->tag == ENEMY && e->obj->tagChange == WEAPON &&	e->obj->isKicked) {
					startTimeDead();
					isFlip = true;
					vy = -0.2f;
					vx = 0;
					SetState(ENEMY_DIE_FLIP);
				}

				if (e->nx != 0) {
					x += dx;
				}
				if (e->ny != 0) {
					y += dy;
				}
			}
			
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (isDead)
	{
		if (canRespawn)
		{
			if (GetTickCount() - TimeDead > KOOMPA_TIME_REVIVAL)
			{
				player->canPicking = false;
				player->isPicking = false;
				TimeDead = 0;
				Revival();
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

		if (player->isPicking)
		{
			UpdatePosition(dt);
		}

		if (!player->canPicking)
		{
			if (player->isPicking)
			{
				player->ChangeState(new PlayerKickState());
				this->isKicked = true;
				canRespawn = false;
				if (player->nx == 1)
				{
					this->vx = 2 * MARIO_WALKING_SPEED;
				}
				else {
					this->vx = -2 * MARIO_WALKING_SPEED;
				}
				player->isPicking = false;
			}

		}
	}
	else {
		UpdateLocation();
	}
}

void ParaKoompa::SetState(STATEOBJECT state)
{
	Koompa::SetState(state);
	switch (state)
	{
	case ENEMY_WALKING_RIGHT:
		nx = 1;
		vx = KOOMBA_WALKING_SPEED;
		break;
	case ENEMY_WALKING_LEFT:
		nx = -1;
		vx = -KOOMBA_WALKING_SPEED;
		break;
	}
}
void ParaKoompa::Revival()
{
	nx = -1;
	y -= 20;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_WALKING_LEFT);
}