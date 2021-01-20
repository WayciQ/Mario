#pragma once
#include "Weapon.h"
class BoomerangWeapon : public Weapon
{
	float startX, startY;
public:
	BoomerangWeapon(float nx,float x, float y);
	~BoomerangWeapon();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void UpdatePosititon(DWORD dt);
};