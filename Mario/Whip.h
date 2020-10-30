#pragma once
#include "Weapon.h"
class Whip : public Weapon
{
public:
	Whip();
	~Whip();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void UpdatePosititon(DWORD dt);
	void Render();
};

