#include "Goomba.h"
Goomba::Goomba(TYPE type) : Enemy()
{
	isDead = false;
	canDel = false;
	this->type = type;
	this->nx =1;
	vx = GOOMBA_WALKING_SPEED;
	this->animation_set = animationsSets->Get(type);
	CurAnimation = animation_set->Get(GOOMBA_WALKING);
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
	vy += MARIO_GRAVITY * dt;
	
	if (isDead)
	{
		vx = 0;
		CurAnimation = animationsSets->Get(type)->Get(GOOMBA_DIE);
		GetTime();
	}
	canDel = GetTickCount() - timeDie < 3000;
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

		if (nx != 0) vx = nx < 0 ? -0.05 : GOOMBA_WALKING_SPEED;
		if (ny != 0) vy = 0;
		
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


