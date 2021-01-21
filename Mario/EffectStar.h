#include "Effect.h"
#define ANIMATION_EFFECTHIT 818
class EffectStar : public Effect
{
public:
	EffectStar();
	~EffectStar(){}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};