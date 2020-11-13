#include "PiranhaPlant.h"
#include "Mario.h"
#include "Camera.h"

PiranhaPlant::PiranhaPlant(TYPE type, float posx, float posy) : Enemy()
{
	isUp = true;
	startTimeUp = 0;
	isShoot = false;
	this->type = type;
	PosX = posx;
	YY = posy;
	typeParent = PLANT;
	PosY = type == PIRANHA_PLANT ? posy + 8 : posy;
	SetState(PLANT_FIRE_DOWN_RIGHT);
}

void PiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x = PosX + 8;
	GameObject::Update(dt);
	UpdatePosition(dt);
	y += dy;
	if (isDead)
	{
		if (canRespawn)
		{
			if (GetTickCount() - TimeDead > 150)
			{
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
			}
		}
	}
	
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void PiranhaPlant::UpdatePosition(DWORD dt)
{
	if (x > camera->cam_x && x < camera->cam_x + camera->width)
	{

		if (upDone && CurAnimation->isLastFrame)
		{
			if (!isShoot) {

				canShoot = true;
			}
			else {
				canShoot = false;
			}
		}
		
		if (isUp)
		{
			vy = -PLANT_SPEED_UP;
			upDone = false;
		}
		else {
			upDone = false;
			vy = PLANT_SPEED_UP;
		}
		if (startTimeUp < 0)
		{
			startTimeUp = TIME_UP;
			isUp = !isUp ? true : false;
		}
		else startTimeUp--;
		if (player->x > this->x)
		{
			nx = 1;
			if (player->y >= this->y)
			{
				ny = player->y < this->y + 31 ? 0 : 1;
				SetState(PLANT_FIRE_DOWN_RIGHT);
			}
			else
			{
				ny = -1;
				SetState(PLANT_FIRE_UP_RIGHT);
			}
		}
		else
		{
			nx = -1;
			if (player->y >= this->y) {

				ny = ny = player->y < this->y + 31 ? 0 : 1;
				SetState(PLANT_FIRE_DOWN_LEFT);
			}
			else
			{
				ny = -1;
				SetState(PLANT_FIRE_UP_LEFT);
			}
		}
		if (y <= PosY - 31)
		{
			upDone = true;
			y = PosY - 31;
		}
	}
	else vy = PLANT_SPEED_UP;
	
	
	if (y >= PosY)
	{
		y = PosY;
		isShoot = false;
	}
		

	
}
void PiranhaPlant::SetState(STATEOBJECT state)
{
	GameObject::SetState(state);
}
void PiranhaPlant::Render()
{
	ChangeAnimation();
	CurAnimation->Render(x, y, 225);
	RenderBoundingBox();
	Sprites::GetInstance()->Get(54001)->Draw(PosX, YY);
}
void PiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PLANE_BBOX_HEIGHT;
	bottom = y + PLANE_BBOX_WIDTH;
}