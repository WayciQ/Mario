#include "Fire.h"
#include "Camera.h"
#include "Mario.h"
#include "Effects.h"
#include "Grid.h"
#define FIRE_WIDTH		24
#define FIRE_HEIGHT		24
#define FIRE_SPEED_X	0.36f
#define FIRE_SPEED_Y	0.45f
#define FIRE_SPEED_PLANT_X	0.15f
#define FIRE_SPEED_PLANT_Y	0.15f

Fire::Fire(int nx, int ny, float x, float y, TAG tag)
{
	type = WEAPON_MARIO;
	this->tag = tag;
	weaponOwner = tag;
	
	SetBBox(FIRE_WIDTH, FIRE_HEIGHT);
	canRespawn = false;
	animation_set = animationsSets->Get(WEAPON_MARIO);
	SetPosition(x, y);
	
	if (nx > 0)
	{
		ChangeAnimation(WEAPON_SHOOT_RIGHT);
		vx = this->tag == ENEMY ? FIRE_SPEED_PLANT_X : player->vx + FIRE_SPEED_X;
	}
	else 
	{
		ChangeAnimation(WEAPON_SHOOT_LEFT);
		vx = this->tag == ENEMY ? -FIRE_SPEED_PLANT_X : player->vx -FIRE_SPEED_X;
	}

	if (ny < 0)
	{
		vy = this->tag == ENEMY ? -FIRE_SPEED_PLANT_Y : player->vy -FIRE_SPEED_Y;
	}
	else if (ny == 0)
	{
		vy = 0.02f;
	}
	else
	{
		vy = this->tag == ENEMY ? FIRE_SPEED_PLANT_Y : player->vy + FIRE_SPEED_Y;
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
	
	if (weaponOwner == PLAYER) {

		vy += WORLD_GRAVITY * dt;
		tagChange = WEAPON;
		typeParent = MARIO;
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
			x += min_tx * dx + nx * 0.8f;
			y += min_ty * dy + ny * 0.8f;

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
							isDead = true;
						}
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
						e->obj->vy = -MARIO_JUMP_DEFLECT_SPEED;
						e->obj->vx = 0;
						auto ef = Effects::CreateEffect(SCORE_100);
						grid->AddMovingObject(ef, e->obj->x, e->obj->y);
						isDead = true;
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
		if (isDead) {
			auto bigbang = Effects::CreateEffect(EFFECT_BIGBANG);
			grid->AddMovingObject(bigbang, x, y);
			player->countShoot = player->countShoot <= 0 ? 0 : player->countShoot - 1;
		}
	}
	else {
		tag = ENEMY;
		tagChange = WEAPON;
		typeParent = PLANT;
		x += dx;
		y += dy;
	}
	if (isDead)
	{
		canDel = true;
	}
}

void Fire::UpdatePosititon(DWORD dt)
{

	if(x < camera-> cam_x || x > camera->cam_x + SCREEN_WIDTH ||  y > camera->cam_y + camera->GetHeight())
	{
		isDead = true;
	}
}
Fire::~Fire()
{

}