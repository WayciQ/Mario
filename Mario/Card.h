#pragma once
#include "Item.h"
class Card : public Item
{
	DWORD timeChange;
public:
	Card(float x, float y);
	~Card() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void UpdatePosition(float dt) {};

};

