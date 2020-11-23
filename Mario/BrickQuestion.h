#pragma once
#include "Brick.h"
class BrickQuestion : public Brick
{
	float curY;
	bool isSpawnItem;
public:
	BrickQuestion(float CurY, TYPE child);
	~BrickQuestion(){}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

