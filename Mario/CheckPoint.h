#pragma once
#include "GameObject.h"
class CheckPoint : public GameObject
{
public:
	CheckPoint() {
		tag = BOX;
		type = CHECKPOINT;
		widthBBox = 16;
		heightBBox = 16;
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

