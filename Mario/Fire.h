#pragma once
#include "Weapon.h"
class Fire : public Weapon
{
public:
	Fire(int nx, int ny, float x, float y, TAG tag);
	~Fire();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void UpdatePosititon(DWORD dt);
};

