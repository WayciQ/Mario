#pragma once
#include "GameObject.h"


class Drain	: public GameObject
{
	STATEOBJECT typeDrain;
	float width;
	float height;
public:
	Drain(STATEOBJECT type, float w, float h);
	~Drain();
	void Render();
	void Update();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

