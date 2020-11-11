#include "NipperPlant.h"
#include "Mario.h"

#define PLANT_SPEED_UP 0.05f;
NipperPlant::NipperPlant(TYPE type, float posx, float posy) : Enemy(type)
{
	isUp = true;
	startTimeUp = 0;
	this->type = type;
	PosX = posx;
	PosY = posy;
	SetState(PLANT_UP);
}
void NipperPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	UpdatePosition(dt);
	y += dy;
}
void NipperPlant::UpdatePosition(DWORD dt)
{
	x = PosX + 8;
	if (startTimeUp < 0)
	{
		startTimeUp = TIME_UP;
		isUp = isUp ? false : true;
	}
	else startTimeUp--;
	if (isUp)
	{
		vy = PLANT_SPEED_UP;
	}
	else {
		vy = -PLANT_SPEED_UP;
	}

	if (y <= PosY - 24)
	{
		y = PosY - 24;
	}
	else if (y >= PosY)
		y = PosY;
}

void NipperPlant::Render()
{
	
	ChangeAnimation();
	CurAnimation->Render(x, y, 225);
	Sprites::GetInstance()->Get(54000)->Draw(PosX, PosY);
}
void NipperPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PLANE_BBOX_HEIGHT;
	bottom = y + PLANE_BBOX_WIDTH;
}