#pragma once
#include "GameObject.h"
class Effect : public GameObject
{
public:
	Animation* CurAnimation;
	Effect();
	~Effect() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

