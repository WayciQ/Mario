#pragma once
#include "Weapon.h"
class Fire : public Weapon
{

public:
	Fire();
	~Fire();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void UpdatePosititon(DWORD dt);

};

