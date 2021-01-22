#include "Effect.h"

Effect::Effect()
{
	tag = EFFECT;
	SetBBox(0, 0);
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	{
		if (isDead) {
			canDel = true;
		}
	};
}

void Effect::Render()
{
	CurAnimation->Render(x, y);
	if (CurAnimation->isLastFrame)
		isDead = true;
}
