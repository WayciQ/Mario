#pragma once
#include "enemy.h"

#define GOOMBA_WALKING_SPEED 0.05;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

class Goomba : public Enemy
{
public:
	Goomba(TYPE type);
	~Goomba();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
