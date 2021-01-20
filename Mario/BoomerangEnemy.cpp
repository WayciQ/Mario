#include "BoomerangEnemy.h"
#include "Grid.h"
#include "Boomerang.h"
#include "Grid.h"
#include "Weapons.h"
#define ENNEMY_WALKING_SPEED 0.05f
#define BOOMERAN_WIDTH_BBOX 48
#define BOOMERAN_HEIGHT_BBOX 72
BoomerangEnemy::BoomerangEnemy() {
	nx = 1;
	countThrow = 0;
	this->type = BOOMERRANG_ENEMY;
	CanThrow = false;
	animation_set = animationsSets->Get(type);
	vx = ENNEMY_WALKING_SPEED;
	SetBBox(BOOMERAN_WIDTH_BBOX, BOOMERAN_HEIGHT_BBOX);
	SetState(ENEMY_WALKING_RIGHT);
	Revival();
}

void BoomerangEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);

	

	if (GetTickCount() - TimeToJump < 4000) {
		
		
		if (GetTickCount() - TimeToMove > 2000) {
			//DebugOut(L"%d\n",nx);
			vx = -vx;
			isThrow = false;
			TimeToMove = GetTickCount();
			TimeToThrow = GetTickCount();
		}
	}
	else {
		SetState(ENEMY_JUMPING_RIGHT);
		TimeToJump = GetTickCount();
	}
	  
	if (GetTickCount() - TimeToThrow < 400) {
		CanThrow = true;
		SetState(ENEMY_SHOOTING_RIGHT);
	}
	else {
		SetState(ENEMY_WALKING_RIGHT);
	}

	if (CanThrow) {
		if (!isThrow) {
			CreateBoomerang();
			isThrow = true;
		}
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
		
		break;
	case ENEMY_WALKING_RIGHT:
		
		break;
	case ENEMY_JUMPING_LEFT:
		vy = -ENNEMY_WALKING_SPEED;
		break;
	case ENEMY_JUMPING_RIGHT:
		vy = -0.8;
		break;
	case ENEMY_SHOOTING_RIGHT: 
		break;
	case ENEMY_DIE_FLIP: case ENEMY_DIE_STAND:
		break;
	
	default:
		break;
	}

}
void BoomerangEnemy::CreateBoomerang()
{
	auto Bom = Weapons::CreateWeapon(BOOMERRANG_WEAPON, nx, ny, x, y);
	grid->AddMovingObject(Bom);
}
void BoomerangEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + widthBBox;
	bottom = y + heightBBox;
}
void BoomerangEnemy::Render()
{
	Enemy::Render();
}
void BoomerangEnemy::Revival()
{
	nx = 1;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_WALKING_RIGHT);
}