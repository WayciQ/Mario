#pragma once
#include "Effect.h"
#define ANIMATION_EFFECTBIGBANG 539
class EffectBigBang : public Effect
{
public:
	EffectBigBang();
	~EffectBigBang() {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

