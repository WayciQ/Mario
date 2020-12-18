#pragma once
#include "Brick.h"
class SwitchBlock : public Brick
{
	bool isChange;
public:
	SwitchBlock();
	~SwitchBlock() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

