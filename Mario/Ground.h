 #pragma once
#include"GameObject.h"
class Ground : public GameObject
{
public:
	Ground(float w, float h);
	~Ground() {};
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

