#include "GameObject.h"
#define ANIMATION_EFFECTHIT 818
class EffectHit : public GameObject
{
public:
	Animation* CurAnimation;
	EffectHit() {
		CurAnimation = Animations::GetInstance()->Get(ANIMATION_EFFECTHIT);
	}
	~EffectHit(){}
	void Render()
	{
		if (CurAnimation->isLastFrame)
			isDead = true;
		CurAnimation->Render(x, y);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (isDead)
			canDel = true;
	}
};