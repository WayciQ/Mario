#pragma once
#include "Enemy.h"
#define KOOMBA_WALKING_SPEED 0.05;

#define KOOMBA_BBOX_WIDTH 16
#define KOOMBA_BBOX_HEIGHT 25
#define KOOMBA_BBOX_HEIGHT_DIE 16

class Koomba : public Enemy
{
public:
	Koomba(TYPE type);
	~Koomba();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void UpdatePosition(DWORD dt);

};

