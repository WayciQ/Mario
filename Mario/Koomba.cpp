#include "Koomba.h"
Koomba::Koomba(TYPE type) : Enemy()
{
	isDead = false;
	this->type = KOOMBA;
	this->nx = 1;
	vx = KOOMBA_WALKING_SPEED;
	this->animation_set = animationsSets->Get(type);
	CurAnimation = animation_set->Get(KOOMBA_WALKING_RIGHT);
}
Koomba::~Koomba() {}
void Koomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOMBA_BBOX_WIDTH;
	bottom = y + KOOMBA_BBOX_HEIGHT;
	if (isDead)
		bottom = y + KOOMBA_BBOX_HEIGHT_DIE;
}

void Koomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	/*vy += MARIO_GRAVITY * dt;*/
	y = 390;

	if (isDead)
	{
		y = 397;
		CurAnimation = animationsSets->Get(NOR_KOOMBA)->Get(KOOMBA_DIE);
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

		x += min_tx * dx + nx;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0)
		{
			vx = -vx;
			if(nx > 0)
			CurAnimation = animationsSets->Get(NOR_KOOMBA)->Get(KOOMBA_WALKING_RIGHT);
			else CurAnimation = animationsSets->Get(NOR_KOOMBA)->Get(KOOMBA_WALKING_LEFT);
		}
		if (ny != 0) vy = 0;
		
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


