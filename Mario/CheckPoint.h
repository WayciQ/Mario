#pragma once
#include "GameObject.h"
class CheckPoint : public GameObject
{
public:
	CheckPoint() {
		tag = BOX;
		type = CHECKPOINT;
		SetBBox(UNIT_GAME, UNIT_GAME);
	}
	~CheckPoint(){}
	void Render() {
		//RenderBoundingBox();
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x;
		t = y;
		r = x + widthBBox;
		b = y + heightBBox;
	};
};

