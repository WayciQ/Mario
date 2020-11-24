#pragma once
#include "Item.h"
class Leaf : public Item
{
public:
	Leaf(float x, float y) :Item(x, y)
	{
		
		type = COIN;
		widthBBox = heightBBox = 16; 
		CurAnimation = animationsSets->Get(LEAF)->Get(BLOCK_STATIC);
	}
	~Leaf() {};
	void Update(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	};
	void UpdatePosition(DWORD dt) {};
};

