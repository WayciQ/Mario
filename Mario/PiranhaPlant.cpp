#include "PiranhaPlant.h"
#include "Mario.h"
#include "Camera.h"
#include "Weapons.h"
#include "Effects.h"
#include "Grid.h"

#define PLANT_SPEED_UP 0.15f
#define PLANT_BIGBANG_X x + 5
#define PLANT_BIGBANG_Y y - 10
#define PLANT_X PosX + 24
#define PLANT_UP_Y this->y + 93
#define PLANT_UP_HEIGHT PosY - 93
#define PLANT_UP_WIDTH YY + 24
#define ANI_DRAIN	54001
#define TIME_DIE	150
PiranhaPlant::PiranhaPlant(TYPE type, float posx, float posy) : Enemy()
{
	isUp = true;
	isShoot = false;
	canShoot = false;
	this->type = type;
	PosX = posx;
	PosY = posy;
	SetBBox(PLANE_BBOX_WIDTH, PLANE_BBOX_HEIGHT);
	animation_set = animationsSets->Get(type);
	typeParent = PLANT;
	SetState(PLANT_SHOOT_DOWN_LEFT);
}

void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	GameObject::Update(dt);
	y += dy;
	UpdatePosition(dt);
	if (isDead)
	{
		if (canRespawn)
		{
			if (GetTickCount() - TimeDead > TIME_DIE)
			{
				auto e = Effects::CreateEffect(EFFECT_BIGBANG);
				grid->AddMovingObject(e, PLANT_BIGBANG_X, PLANT_BIGBANG_Y);
				canDel = true;
				TimeDead = 0;
			}
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() != 0)
	{
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->tag == ENEMY)
			{
				if (e->obj->tagChange == WEAPON && e->obj->isKicked)
				{
					startTimeDead();
					SetState(ENEMY_DIE_FLIP);
				}
				else {
					if (e->nx != 0) {
						x += dx;
					}
				}
			}
		}
	}
	
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void PiranhaPlant::UpdatePosition(DWORD dt)
{
	x = PLANT_X;
	if (GetTickCount() - startTimeUp > TIME_UP)
	{
		startTimeUp = GetTickCount();
		isUp = isUp == false ? true : false;
		if (isUp)
		{
			SetBBox(PLANE_BBOX_WIDTH, PLANE_BBOX_HEIGHT);
			vy = -PLANT_SPEED_UP;
			upDone = false;
		}
		else {
			SetBBox(0, 0);
			upDone = false;
			vy = PLANT_SPEED_UP;
		}
	}

	
	if (upDone && CurAnimation->isLastFrame)
	{
		if (canShoot)
		{
			auto w = Weapons::CreateWeapon(FIRE_FIRE, nx, ny, x, y, tag);
			grid->AddMovingObject(w, x, y);
			isShoot = true;
			canShoot = false;
		}
	}
	

		

	if (player->x > this->x)
	{
		nx = 1;
		if (player->y >= this->y)
		{
			ny = player->y < PLANT_UP_Y ? 0 : 1;
			SetState(PLANT_SHOOT_DOWN_RIGHT);
		}
		else
		{
			ny = -1;
			SetState(PLANT_SHOOT_UP_RIGHT);
		}
	}
	else
	{
		nx = -1;
		if (player->y >= this->y) {

			ny = ny = player->y < PLANT_UP_Y ? 0 : 1;
			SetState(PLANT_SHOOT_DOWN_LEFT);
		}
		else
		{
			ny = -1;
			SetState(PLANT_SHOOT_UP_LEFT);
		}
	}


	if (y <= PLANT_UP_HEIGHT)
	{
		y = PLANT_UP_HEIGHT;
		upDone = true;
		if (!isShoot)
			canShoot = true;
	}
	if (y >= PosY)
	{
		isShoot = false;
		y = PosY;
	}
		

	
}
void PiranhaPlant::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
}
void PiranhaPlant::Render()
{
	ChangeAnimation();
	CurAnimation->Render(x, y);
	//RenderBoundingBox();
	Sprites::GetInstance()->Get(ANI_DRAIN)->Draw(PosX, PosY);
}
void PiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + widthBBox;
	bottom = y + heightBBox;
	
}