#pragma once
#include "Effect.h"
#define ANIMATION 100000
class Number : public Effect
{
public:
	Number() {
		SetBBox(UNIT_GAME, UNIT_GAME);
		CurAnimation = Animations::GetInstance()->Get(ANIMATION);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	void Render() {
		CurAnimation->Render(x, y);
	}
};

