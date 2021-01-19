#pragma once
#include "Enemy.h"
class BoomerangEnemy : public Enemy
{
	DWORD TimeToMove;
	DWORD TimeToThrow;
	bool CanThrow;
public:
	BoomerangEnemy();
	~BoomerangEnemy(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Revival();
	void SetState(STATEOBJECT state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

