#pragma once
#include "Item.h"
class SwitchBlock : public Item
{
	bool isChange;
public:
	SwitchBlock(float x, float y);
	~SwitchBlock() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

