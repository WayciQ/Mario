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
	virtual void Render();
	virtual void Update();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

