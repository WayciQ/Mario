#pragma once
#include "Enemy.h"
#define KOOMBA_WALKING_SPEED 0.05;
#define KOOMBA_BBOX_WIDTH 16
#define KOOMBA_BBOX_HEIGHT 27
#define KOOMBA_BBOX_HEIGHT_DIE 16
#define KOOMPA_TIME_REVIVAL 5000

class Koompa : public Enemy
{
	
public:
	int maxLeft, maxRight;
	Koompa();
	~Koompa() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(DWORD dt);
	virtual void UpdateLocation();
	virtual void Revival() {};
	virtual void SetState(STATEOBJECT state);
	virtual void Render() { Enemy::Render(); };
};

