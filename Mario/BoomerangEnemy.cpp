#include "BoomerangEnemy.h"
#include "Grid.h"
#include "Boomerang.h"
#define ENNEMY_WALKING_SPEED 0.05f;
BoomerangEnemy::BoomerangEnemy() {
	this->type = BOOMERRANG_ENEMY;
	animation_set = animationsSets->Get(type);
	SetBBox(48, 72);
	Revival();
}

void BoomerangEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);

	if (GetTickCount() - TimeToMove > 1000) {
	//DebugOut(L"%d\n",nx);
		nx = -nx;
		TimeToMove = GetTickCount();
	}

	if (nx > 0) {
		SetState(ENEMY_WALKING_RIGHT);
	}
	else {
		SetState(ENEMY_WALKING_LEFT);
	}
	if (GetTickCount() - TimeToThrow > 3000) {
		CanThrow = CanThrow == true ? false : true;
		TimeToThrow = GetTickCount();
	}
	if (CanThrow) {
		if(nx > 0) SetState(ENEMY_JUMPING_RIGHT);
		else SetState(ENEMY_JUMPING_LEFT);
	}
	vy += WORLD_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		// block 
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.004f;

		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++) {
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->tag == GROUND) {


				if (e->obj->type == GROUND_BOX)
				{
					if (e->nx != 0)
					{
						x += dx;
					}
				}
				else
				{
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void BoomerangEnemy::SetState(STATEOBJECT state) {
	GameObject::SetState(state);
	switch (state)
	{
	case ENEMY_WALKING_LEFT:
		vx = -ENNEMY_WALKING_SPEED;
		break;
	case ENEMY_WALKING_RIGHT:
			
		break;
	case ENEMY_JUMPING_LEFT:
		
		break;
	case ENEMY_JUMPING_RIGHT:
		vx = ENNEMY_WALKING_SPEED;
		break;
	case ENEMY_DIE_FLIP: case ENEMY_DIE_STAND:
		break;
	default:
		break;
	}

}
void BoomerangEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + widthBBox;
	bottom = y + heightBBox;
}
void BoomerangEnemy::Revival()
{
	nx = -1;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_WALKING_LEFT);
}