#pragma once
#include "Item.h"
class Coin : public Item
{
	bool isStatic;
	int time;
public:
	Coin(float x, float y, bool isStatic = true);
	~Coin() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

