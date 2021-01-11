#include "Effect.h"
#define ANIMATION_EFFECTHIT 818
class EffectHit : public Effect
{
public:
	
	EffectHit() {	
		CurAnimation = Animations::GetInstance()->Get(ANIMATION_EFFECTHIT);
	}
	~EffectHit(){}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		
	}
};