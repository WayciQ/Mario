#include "Goomba.h"
Goomba::Goomba() {
	isDead = false;
	nx = 1;	
	vx = GOOMBA_WALKING_SPEED;
	CurAnimation = animation_set->Get(GOOMBA_WALKING);
}
Goomba::~Goomba(){}
void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += MARIO_GRAVITY * dt;
	if (!isDead) {
		CurAnimation = animation_set->Get(GOOMBA_WALKING);
	}
	else {
		vx = 0;
		CurAnimation = animation_set->Get(GOOMBA_DIE);
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
		
		x += min_tx * dx + nx * 0.7f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.7f;

		if (nx != 0) vx = nx < 0 ? -0.05 : GOOMBA_WALKING_SPEED;
		if (ny != 0) vy = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Goomba::Render()
{
	CurAnimation->Render(x, y, 255);
	RenderBoundingBox();
}
