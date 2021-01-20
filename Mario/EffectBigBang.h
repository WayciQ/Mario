#include "Effect.h"
#include "Camera.h"
#define ANIMATION_EFFECTBIGBANG 539
class EffectBigBang : public Effect
{
public:
	EffectBigBang();
	~EffectBigBang() {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	
};