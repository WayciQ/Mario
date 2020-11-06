#pragma once
#include "Brick.h"
class BrickQuestion : public Brick
{
public:
	BrickQuestion();
	~BrickQuestion(){}
	void Update()	;
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

