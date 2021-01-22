#include "NipperPlant.h"
#include "Mario.h"
#include "Effects.h"
#include "Grid.h"


#define PLANT_SPEED_UP 0.15f
#define PLANT_BIGBANG_X x + 5
#define PLANT_BIGBANG_Y y - 10
#define PLANT_UP_HEIGHT PosY - 72
#define PLANT_UP_WIDTH PosX + 18
#define ANI_DRAIN	54000
NipperPlant::NipperPlant( float posx, float posy) : Enemy()
{
	isUp = true;
	startTimeUp = 0;
	SetBBox(PLANE_BBOX_WIDTH, PLANE_BBOX_HEIGHT);
	this->type = NIPPER_PLANT;
	animation_set = animationsSets->Get(type);
	typeParent = PLANT;
	PosX = posx;
	PosY = posy;
	SetState(PLANT_UP);
}
void NipperPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	UpdatePosition(dt);
	y += dy;
	if (isDead)
	{
		if (canRespawn)
		{
			if (GetTickCount() - TimeDead > 150)
			{
				auto e = Effects::CreateEffect(EFFECT_BIGBANG);
				grid->AddStaticObject(e, PLANT_BIGBANG_X, PLANT_BIGBANG_Y);
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
void NipperPlant::UpdatePosition(DWORD dt)
{
	x = PLANT_UP_WIDTH;
	if (startTimeUp < 0)
	{
		startTimeUp = TIME_UP;
		isUp = isUp ? false : true;
	}
	else startTimeUp--;

	if (isUp)
	{
		SetBBox(PLANE_BBOX_WIDTH, PLANE_BBOX_HEIGHT);
		vy = PLANT_SPEED_UP;
	}
	else {
		vy = -PLANT_SPEED_UP;
	}

	if (y <= PLANT_UP_HEIGHT)
	{
		y = PLANT_UP_HEIGHT;
	}
	else if (y >= PosY) {
		y = PosY; 
		SetBBox(0, 0);
	}
		
}

void NipperPlant::Render()
{
	ChangeAnimation();
	CurAnimation->Render(x, y);
	Sprites::GetInstance()->Get(ANI_DRAIN)->Draw(PosX, PosY);
}
void NipperPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y; 
	right = x + widthBBox;
	bottom = y + heightBBox;
}