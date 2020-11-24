#include "Mushroom.h"
#include "Mario.h"
#define SPEED_MUSHROOM 0.05f
Mushroom::Mushroom(TYPE type, float x, float y) : Item(x,y)
{
	this->type = type;
	widthBBox = heightBBox = 16;
	CurAnimation = animationsSets->Get(type)->Get(BLOCK_STATIC);
	nx = player->nx;
	vy = -0.2f;
	if (nx > 0)
	{
		vx = SPEED_MUSHROOM;
	}
	else {
		vx = -SPEED_MUSHROOM;
	}
}
void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += WORLD_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if(isDead) canDel = true;

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

					vy = 0;
				}

			}

		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}