#include "TropaKoompa.h"
#include "Mario.h"
#include "PlayerKickState.h"
TropaKoompa::TropaKoompa() : Koompa()
{
	this->type = TROPA_KOOMPA;
	jumped = false;
	nx = -1;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_JUMPING_LEFT);
}
void TropaKoompa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;


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
		//y += min_ty * dy + ny * 0.4f;

		if (ny == -1) {
			if (!jumped && !isFlip)
				vy = -0.25f;
			else vy = 0;
		};
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (e->obj->tag == GROUND) {
				if (e->ny == -1 && jumped) {
					maxLeft = e->obj->x;
					maxRight = e->obj->x + e->obj->widthBBox - widthBBox;
				}
				if (e->obj->type == GROUND_BOX) {
					
					if (e->nx != 0) {
						x += dx;
					}
					
				}
				else if ((e->obj->type == BLOCK_QUESTION || e->obj->type == BLOCK_BREAKABLE) && isDead) {
					if (e->nx != 0) {
						e->obj->startTimeDead();
						vx = -vx;
					}
				}
				else {
					if (e->nx != 0)
					{
						this->nx = -this->nx;
						if (!isDead && jumped)
						{
							if (this->nx < 0)
								SetState(ENEMY_WALKING_LEFT);
							else
								SetState(ENEMY_WALKING_RIGHT);
						}
						else if (!isDead && !jumped)
						{
							if (this->nx > 0)
								SetState(ENEMY_JUMPING_LEFT);
							else
								SetState(ENEMY_JUMPING_RIGHT);
						}else
							vx = -vx;
					}
					if (e->ny == 1) {
						vy = 0;
					}
				}
				
			}
			else if (e->obj->tag == ENEMY) {
				e->obj->startTimeDead();
				e->obj->isFlip = true;
				e->obj->vy = -0.2f;
				e->obj->vx = 0;
				e->obj->SetState(ENEMY_DIE_FLIP);
				if (e->nx != 0) {
					x += dx;
				}
				if (e->ny != 0) {
					y += dy;
				}
			}
			else if (e->obj->tag == ITEM) {
				x += dx;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


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
			if (GetTickCount() - TimeDead > KOOMPA_TIME_REVIVAL - 2000)
			{

				if (!isFlip)
				{
					state = KOOMPA_RESPAWN;
				}
				else
				{
					state = KOOMPA_RESPAWN_FLIP;
				}
				vx = 0;
			}
			if (GetTickCount() - TimeDead > KOOMPA_TIME_REVIVAL)
			{
				player->canPicking = false;
				player->isPicking = false;
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
	else
	{
		if (jumped)
		{
			if (nx > 0)
				state = ENEMY_WALKING_RIGHT;
			else state = ENEMY_WALKING_LEFT;
		}
		else
		{
			if (nx > 0)
			{
				SetState(ENEMY_JUMPING_RIGHT);
			}
			else SetState(ENEMY_JUMPING_LEFT);
		}
	}
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
	y -=20;
	nx = 1;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	jumped = true;
	SetState(ENEMY_WALKING_LEFT);
}