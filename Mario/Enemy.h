#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
	
public:
	Enemy(TYPE type) {
		tag = ENEMY;
		isDead = false;
		animation_set = animationsSets->Get(type);
	}
	Animation* CurAnimation;
	bool checkDead;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(float dt) {};
	virtual void Render();
	virtual void CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void ChangeAnimation(STATEOBJECT state);
	virtual void Revival() {};
};

