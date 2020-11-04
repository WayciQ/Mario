#pragma once
#include"GameObject.h"
class Ground : public GameObject
{
	float width;
	float height;
public:
	Ground(float w, float h);
	~Ground() {};
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

