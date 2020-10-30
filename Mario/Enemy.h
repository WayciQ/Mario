#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
	
public:
	Enemy() {
		tag = ENEMY;
		isDead = false;
	}
	Animation* CurAnimation;
	int timeDie;
	bool ishitting;
	virtual void GetTime() { timeDie = GetTickCount(); canDel = false; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(float dt) {};
	virtual void Render();
	virtual void CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};

};

