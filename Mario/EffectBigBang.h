#include "GameObject.h"
#define ANIMATION_EFFECTBIGBANG 539
class EffectBigBang : public GameObject
{
public:
	Animation* CurAnimation;
	EffectBigBang() {
		CurAnimation = Animations::GetInstance()->Get(ANIMATION_EFFECTBIGBANG);
	}
	~EffectBigBang() {}
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