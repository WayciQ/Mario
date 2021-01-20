#pragma once
#include "Enemy.h"
#include "BoomerangWeapon.h" 
class BoomerangEnemy : public Enemy
{
	DWORD TimeToMove;
	DWORD TimeToJump;
	DWORD TimeToThrow;
	bool CanThrow;
	bool isThrow;
	int countThrow;
public:
	BoomerangEnemy();
	~BoomerangEnemy(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Revival();
	void SetState(STATEOBJECT state);
	void CreateBoomerang();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};

