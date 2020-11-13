#pragma once
#include "enemy.h"

#define GOOMBA_WALKING_SPEED 0.05;
#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9
#define GOOMBA_TIME_DIE 300

class Goomba : public Enemy
{
public:
	Goomba();
	~Goomba() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(DWORD dt) {};
	virtual void Revival() {};
	virtual void SetState(STATEOBJECT state);
};
