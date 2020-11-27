#pragma once
#include "Brick.h"

class BrickBreakable : public Brick
{
	bool canBreak;
public:
	BrickBreakable(TYPE child);
	~BrickBreakable() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

