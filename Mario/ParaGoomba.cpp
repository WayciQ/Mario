#include "ParaGoomba.h"
#include "Camera.h"
#include "Mario.h"
#define PARA_GOOMBA_BBOX_WIDTH 21
#define PARA_GOOMBA_BBOX_HEIGHT 24
ParaGoomba::ParaGoomba() : Goomba()
{
	this->type = PARA_GOOMBA;
	jumped = false;
	isDead = false;
	canDel = false;
	canRespawn = false;
	vx = GOOMBA_WALKING_SPEED;
	SetState(ENEMY_JUMPING_RIGHT);
}

void ParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	UpdatePosition(dt);
	vy += WORLD_GRAVITY * dt;
	ChangeAnimation();
	if (isDead)
	{
		if (canRespawn)
		{
			vx = 0;
			if (!jumped && !isFlip)
			{
				jumped = true;
				Revival();
				return;
			}
			if (isFlip)
			{
				if (GetTickCount() - TimeDead > GOOMBA_TIME_DIE)
				{
					if (isFlip) canDel = true;
					TimeDead = 0;
				}
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
		y += min_ty * dy + ny * 0.4f;

		/*if (nx != 0) vx = nx < 0 ? -0.05 : GOOMBA_WALKING_SPEED;*/
		if (ny == -1) {
			if (!jumped && !isFlip)
				vy = -0.3f;
			else vy = 0;
		};
		if (isDead == true && ny == -1)
		{
			y += dy;
			canDel = true;
		}
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

				}

			}
			if (e->obj->tag == ENEMY)
			{
				if (e->nx != 0)
				{
					x += dx;
				
				}
				if (e->ny != 0)
				{
					y += dy;
				}
				/*if (e->obj->tagChange == WEAPON && e->obj->isKicked)
				{
					startTimeDead();
					isFlip = true;
					vy = -0.2f;
					vx = 0;
					SetState(ENEMY_DIE_FLIP);
				}*/
			}
			
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void ParaGoomba::SetState(STATEOBJECT state)
{
	Goomba::SetState(state);
}
void ParaGoomba::Revival()
{
	isDead = false;
	canDel = false;
	canRespawn = false;
	vx = GOOMBA_WALKING_SPEED;
	nx = 1;
	jumped = true;
	SetState(ENEMY_WALKING_RIGHT);

}
#define DISTANCE_FL 100
void ParaGoomba::UpdatePosition(DWORD dt)
{
	if ((x > camera->cam_x || x < camera->cam_x + camera->width) && !jumped)
	{	
		if ((x > player->x + DISTANCE_FL))
		{
			vx = -GOOMBA_WALKING_SPEED;
		}
		else if((x < player->x - DISTANCE_FL)) {
			vx = GOOMBA_WALKING_SPEED;
		}
	}

	GameObject::Update(dt);
}
void ParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (jumped)
	{
		right = x + GOOMBA_BBOX_WIDTH;
		bottom = y + GOOMBA_BBOX_HEIGHT;
	}
	else {
		right = x + PARA_GOOMBA_BBOX_WIDTH;
		bottom = y + PARA_GOOMBA_BBOX_HEIGHT;
	}

	if (isDead)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
}