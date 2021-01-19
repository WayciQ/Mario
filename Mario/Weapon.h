#pragma once
#include "GameObject.h"

class Weapon: public GameObject
{
public:
	Weapon();
	~Weapon() {};
	Animation* CurAnimation;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void UpdatePosititon(DWORD dt) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render();
	virtual void ChangeAnimation(STATEOBJECT state) {
		CurAnimation = animation_set->Get(state);
	}
};