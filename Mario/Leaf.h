#pragma once
#include "Item.h"
class Leaf : public Item
{
	float CenX,CenY;
	bool isFalling;
public:
	Leaf(float x, float y);
	~Leaf() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void UpdatePosition(DWORD dt);
};

