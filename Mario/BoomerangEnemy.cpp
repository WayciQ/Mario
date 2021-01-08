#include "BoomerangEnemy.h"
BoomerangEnemy::BoomerangEnemy() {

}

void BoomerangEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}

void BoomerangEnemy::Revival()
{
	nx = -1;
	y -= 20;
	isDead = false;
	canRespawn = false;
	isKicked = false;
	SetState(ENEMY_WALKING_LEFT);
}