#pragma once
#include "GameObject.h"

#define TIME_UP 200
#define PLANT_SPEED_UP 0.15f
#define PLANE_BBOX_HEIGHT 96
#define PLANE_BBOX_WIDTH 48
class Enemy : public GameObject
{
	
public:
	Enemy() {
		tag = ENEMY;
		tagChange = ENEMY;
		isDead = false;
	}
	Animation* CurAnimation;
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(float dt) {};
	virtual void Render();
	virtual void CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void ChangeAnimation();
	virtual void Revival() {};
	virtual void startTimeDead(){ TimeDead = GetTickCount(); isDead = true;  canRespawn = true; }
};

