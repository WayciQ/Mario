#pragma once
#include "Item.h"

class Mushroom: public Item
{
public:
	Mushroom(TYPE type, float x, float y);
	~Mushroom() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

