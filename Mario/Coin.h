#pragma once
#include "Item.h"
class Coin : public Item
{
	bool isStatic;
	bool isCoinChange;
	int time;
public:
	Coin(float x, float y,STATEOBJECT state = BLOCK_STATIC, bool isStatic = true);
	~Coin() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

