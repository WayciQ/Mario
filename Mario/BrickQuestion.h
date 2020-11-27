#pragma once
#include "Brick.h"
class BrickQuestion : public Brick
{
	float curY;
	bool isDone;
public:
	BrickQuestion(float CurY, TYPE child);
	~BrickQuestion(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

