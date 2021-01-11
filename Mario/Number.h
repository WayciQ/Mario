#pragma once
#include "Effect.h"
#define SPEED_X 0.05f
#define ANIMATION 100000
class Number : public Effect
{
public:
	Number() {
		SetBBox(16, 16);
		CurAnimation = Animations::GetInstance()->Get(ANIMATION);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

