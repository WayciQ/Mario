#pragma once
#include "GameObject.h"
class Whip : public GameObject
{
	static Whip* __instance;
public:
	
	Whip();
	~Whip();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	static Whip* GetInstance();
};


