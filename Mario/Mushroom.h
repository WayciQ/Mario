#pragma once
#include "Item.h"
class Mushroom: public Item
{
public:
	Mushroom(TYPE type,float x,float y) : Item(x,y)
	{
		
		this->type = type;
		widthBBox = heightBBox = 16; 
		CurAnimation = animationsSets->Get(type)->Get(BLOCK_STATIC);
	}
	~Mushroom() {};
	void Update(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	};
};

