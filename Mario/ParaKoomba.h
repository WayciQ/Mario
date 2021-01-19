#pragma once
#include "Koompa.h"
class ParaKoompa : public Koompa
{
	DWORD TimeFly;
	bool FlyUp;
	bool isFlying;
	bool isJumped;
public:
	ParaKoompa(STATEOBJECT object);
	~ParaKoompa() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetState(STATEOBJECT state);
	void Revival(STATEOBJECT object);
	void UpdateStateFly(DWORD dt);
};

