#include "Effect.h"

Effect::Effect()
{
	tag = EFFECT;
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
