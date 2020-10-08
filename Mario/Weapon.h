#pragma once
#include "Mario.h"
class Weapon : public GameObject
{
public:
	bool allowHit;
	Weapon() : GameObject()
	{
		tag = WEAPON;
		isDead = false;
	}
	~Weapon();
	Animation* CurAnimation;
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void UpdatePosititon(DWORD dt) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
};

