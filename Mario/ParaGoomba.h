#pragma once
#include "Goomba.h"
class ParaGoomba : public Goomba
{
	bool jumped;
public:
	ParaGoomba();
	~ParaGoomba() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetState(STATEOBJECT state);
	void UpdatePosition(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Revival();
};

