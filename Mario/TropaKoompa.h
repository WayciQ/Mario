#pragma once
#include "Koompa.h"
class TropaKoompa : public Koompa
{
	bool jumped;
public:
	TropaKoompa();
	~TropaKoompa(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void SetState(STATEOBJECT state);
	void Revival();

};

