#pragma once
#include "Goomba.h"
class BasGoomba : public Goomba
{
public:
	BasGoomba();
	~BasGoomba() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Revival();
};

