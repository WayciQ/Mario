#pragma once
#include "GameObject.h"
class CheckPoint : public GameObject
{
public:
	CheckPoint() {}
	~CheckPoint(){}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom){}
	void Render() {}
};

