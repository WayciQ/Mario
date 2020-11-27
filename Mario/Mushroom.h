#pragma once
#include "Item.h"

class Mushroom: public Item
{
	bool isRespawn;
	float posY;
public:
	Mushroom(TYPE type, float x, float y);
	~Mushroom() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

