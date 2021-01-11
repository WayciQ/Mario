#pragma once
#include "Enemy.h"
#define KOOMPA_WALKING_SPEED 0.15;
#define KOOMPA_JUMP_DEFLECT_SPEED 0.6f;
#define KOOMPA_JUMP_SPEED 0.75f;
#define KOOMPA_BBOX_WIDTH 48
#define KOOMPA_BBOX_HEIGHT 81
#define KOOMPA_BBOX_HEIGHT_DIE 48
#define KOOMPA_TIME_REVIVAL 7000
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

