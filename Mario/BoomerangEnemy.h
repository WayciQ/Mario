#pragma once
#include "Enemy.h"
class BoomerangEnemy : public Enemy
{
public:
	BoomerangEnemy();
	~BoomerangEnemy(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Revival();
};

