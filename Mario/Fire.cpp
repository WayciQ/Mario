#include "Fire.h"
#include "Camera.h"
#include "Mario.h"

#define FIRE_WIDTH		8
#define FIRE_HEIGHT		8
#define FIRE_SPEED_X	0.12f
#define FIRE_SPEED_Y	0.15f
#define FIRE_SPEED_PLANT_X	0.05f
#define FIRE_SPEED_PLANT_Y	0.05f

Fire::Fire(int nx, int ny, float x, float y, TAG tag)
{
	type = WEAPON_MARIO;
	this->tag = tag;
	fireFrom = tag;
	SetBBox(FIRE_WIDTH, FIRE_HEIGHT);
	canRespawn = false;
	animation_set = animationsSets->Get(WEAPON_MARIO);
	SetPosition(x, y);
	
	if (nx > 0)
	{
		ChangeAnimation(FIRE_FIRE_RIGHT);
		vx = tag == ENEMY ? FIRE_SPEED_PLANT_X : player->vx + FIRE_SPEED_X;
	}
	else 
	{
		ChangeAnimation(FIRE_FIRE_LEFT);
		vx = tag == ENEMY ? -FIRE_SPEED_PLANT_X : player->vx -FIRE_SPEED_X;
	}

	if (ny < 0)
	{
		vy = tag == ENEMY ? -FIRE_SPEED_PLANT_Y : player->vx -FIRE_SPEED_Y;
	}
	else if (ny == 0)
	{
		vy = 0.02f;
	}
	else
	{
		vy = tag == ENEMY ? FIRE_SPEED_PLANT_Y : player->vx+ FIRE_SPEED_Y;
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
	
	GameObject::Update(dt);
	UpdatePosititon(dt);
	if (isDead)
	{
		ChangeAnimation(BIGBANG);
	}
	if (canRespawn)
	{
		if (GetTickCount() - TimeDead > 50)
		{
			canDel = true;
			TimeDead = 0;
		}
	}
	if (fireFrom == PLAYER) {
		vy += WORLD_GRAVITY * dt;
		tag = WEAPON;
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
					if (e->obj->type != GROUND_BOX)
					{
						if (e->nx != 0)
						{
							vx = 0;
							vy = 0;
							e->obj->isDead = true;
							startTimeDead();
						}
						/*if (e->obj->type == BLOCK_QUESTION)
						{
							vy = 0;
							

						}*/

					}
					else {
						if (e->nx != 0)
						{
							x += dx;
						}
					}
					
					break;
				case ENEMY:
					if (e->nx != 0 || e->ny != 0)
					{
						e->obj->vx = 0;
						e->obj->startTimeDead();
						e->obj->isFlip = true;
						e->obj->SetState(ENEMY_DIE_FLIP);
						e->obj->vy = -0.2f;
						e->obj->vx = 0;
						startTimeDead();
						vx = 0;
					}
					break;
				case WEAPON:
					{
						x += dx;
						y += dy;
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
	else {
		tagChange = WEAPON;
		x += dx;
		y += dy;
	}
	
}
void Fire::CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{
	
	
	
}

void Fire::UpdatePosititon(DWORD dt)
{

	if(x < camera-> cam_x || x > camera->cam_x + camera->GetWidth() ||  y > camera->cam_y + camera->GetHeight())
	{
		startTimeDead();
		CurAnimation = animation_set->Get(BIGBANG);
	}
	GameObject::Update(dt);
}
Fire::~Fire()
{

}