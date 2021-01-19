#pragma once
#include "Koompa.h"
class ParaKoompa : public Koompa
{	
public:
	ParaKoompa(STATEOBJECT object);
	~ParaKoompa() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetState(STATEOBJECT state);
	void Revival(STATEOBJECT object);
};

