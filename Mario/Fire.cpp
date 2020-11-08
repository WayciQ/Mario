#include "Fire.h"
#include "Camera.h"
#include "Mario.h"

#define FIRE_WIDTH		8
#define FIRE_HEIGHT		8
#define FIRE_SPEED_X	0.1f
#define FIRE_SPEED_Y	0.15f

Fire::Fire() 
{
	type = WEAPON_MARIO;
	SetBBox(FIRE_WIDTH, FIRE_HEIGHT);
	checkDead = false;
	float px, py;
	player->GetPosition(px, py);
	animation_set = animationsSets->Get(WEAPON_MARIO);
	nx = player->nx;
	SetPosition(px, py);
	if (nx > 0)
	{
		ChangeAnimation(FIRE_FIRE_RIGHT);
		vx = player->vx + FIRE_SPEED_X;
		
	}
	else 
	{
		vx = player->vx - FIRE_SPEED_X;
		ChangeAnimation(FIRE_FIRE_LEFT);
	}
}
void Fire::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}
void Fire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += WORLD_GRAVITY * dt;
	GameObject::Update(dt);

	UpdatePosititon(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	if (isDead)
	{
		ChangeAnimation(FIRE_GONE);
	}
	if (checkDead)
	{
		if (GetTickCount() - TimeDead > 50)
		{
			canDel = true;
			TimeDead = 0;
		}
	}
	
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
		x += min_tx * dx + nx * 0.01f;
		y += min_ty * dy + ny * 0.001f;

		if (ny == -1)
		{
			vy = -FIRE_SPEED_Y;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			switch (e->obj->tag)
			{
			case GROUND:
				if (e->obj->type != BOX_GROUND)
				{
					if (e->nx != 0)
					{
						vx = 0;
						vy = 0;
						startTimeDead();
					}

				}
				else {
					if (e->nx != 0)
					{
						x += dx;
					}
				}
				if (e->obj->type == BRICK_QUESTION)
				{

					vy = 0;
					e->obj->isDead = true;


				}
				break;
			case ENEMY:
				if (e->nx != 0 || e->ny != 0)
				{
					e->obj->vx = 0;
					e->obj->startTimeDead();
					startTimeDead();
					vx = 0;
				}
				break;
			default:
				break;
			}
		}

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Fire::CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{
	
	
	
}

void Fire::UpdatePosititon(DWORD dt)
{
	

	if(x < camera-> cam_x || x > camera->cam_x + camera->width ||  y > camera->cam_y + camera->height)
	{
		isDead = true;
		CurAnimation = animation_set->Get(FIRE_GONE);
	}

	GameObject::Update(dt);
}
Fire::~Fire()
{

}