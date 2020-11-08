#pragma once
#include "Brick.h"
class BrickQuestion : public Brick
{
	float curY;
public:
	BrickQuestion(float CurY);
	~BrickQuestion(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

