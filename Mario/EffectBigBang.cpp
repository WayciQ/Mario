#include "EffectBigBang.h"

EffectBigBang::EffectBigBang()
{
	CurAnimation = Animations::GetInstance()->Get(ANIMATION_EFFECTBIGBANG);
}
void EffectBigBang::Render()
{
	CurAnimation->Render(x, y);
	if (CurAnimation->isLastFrame)
		isDead = true;
}
