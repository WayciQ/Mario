#pragma once
#include "Brick.h"

class BrickBreakable : public Brick
{
	
public:
	BrickBreakable();
	~BrickBreakable() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

