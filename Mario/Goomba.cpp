#include "Goomba.h"
#define GOOMBA_TIME_DIE 300
Goomba::Goomba(TYPE type) : Enemy(type)
{
	isDead = false;
	canDel = false;
	canRespawn = false;
	this->type = type;
	this->nx =1;
	vx = GOOMBA_WALKING_SPEED;
	SetState(GOOMBA_WALKING);
}
Goomba::~Goomba(){}
void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;
	bottom = y + GOOMBA_BBOX_HEIGHT;
	if(isDead)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
}

void Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;
	ChangeAnimation();
	if (isDead)
	{
		vx = 0;
		if (isFlip)
		{
			if (canRespawn)
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
		if (ny != 0) vy = 0;

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
						isFlip = true;
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


