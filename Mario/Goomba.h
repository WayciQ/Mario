#pragma once
#include "enemy.h"

#define GOOMBA_WALKING_SPEED 0.15f;
#define GOOMBA_JUMP_DEFLECT_SPEED 0.6f;
#define GOOMBA_JUMP_SPEED 0.9f;
#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 48
#define GOOMBA_BBOX_HEIGHT_DIE 27
#define GOOMBA_TIME_DIE 300
#define DISTANCE_FL 390
class Goomba : public Enemy
{
public:
	Goomba();
	~Goomba() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(DWORD dt);
	virtual void Revival() {};
	virtual void SetState(STATEOBJECT state);
};
