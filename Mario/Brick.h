#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class Brick : public GameObject
{
	STATEOBJECT type;
public:
	Brick(STATEOBJECT types);
	~Brick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};