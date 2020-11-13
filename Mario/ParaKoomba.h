#pragma once
#include "Koompa.h"
#define KOOMPA_TIME_REVIVAL 5000
class ParaKoompa : public Koompa
{	
public:
	ParaKoompa();
	~ParaKoompa() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetState(STATEOBJECT state);
	void Revival();
};

