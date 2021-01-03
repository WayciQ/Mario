#pragma once
#include "Brick.h"

class BrickBreakable : public Brick
{
	bool canBreak;
	bool isDone;
	float curY;
	int NumberHit;
public:
	BrickBreakable(int curY,TYPE child,int Num);
	~BrickBreakable() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

