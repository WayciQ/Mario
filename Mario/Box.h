#pragma once
#include "GameObject.h"
class Box	: public GameObject
{
	float width;
	float height;
public:
	Box(float w, float h);
	~Box();
	void Render();
	void Update();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

