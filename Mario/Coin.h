#pragma once
#include "Item.h"
class Coin : public Item
{
public:
	Coin(float x, float y,bool isStatic = true) : Item(x, y)
	{
		
		type = COIN;
		widthBBox = heightBBox = 16;
		CurAnimation = animationsSets->Get(COIN)->Get(BLOCK_STATIC);
	}
	~Coin() {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	};
};

