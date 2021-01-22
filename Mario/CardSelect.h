#pragma once
#pragma once
#pragma once
#include "Effect.h"
#define ANIMATION_1 90021
#define ANIMATION_2 90031
#define ANIMATION_3 90041
#define TIME_UP 5000
#define SPEED_UP 0.5f
class CardSelect : public Effect
{
	DWORD TimeUp;
public:
	CardSelect(STATEOBJECT card) {
		if (card == CARD_MUSHROOM) {
			CurAnimation = Animations::GetInstance()->Get(ANIMATION_1);
		}
		else if (card == CARD_FLOWER) {
			CurAnimation = Animations::GetInstance()->Get(ANIMATION_2);
		}
		else if (card == CARD_STAR) {
			CurAnimation = Animations::GetInstance()->Get(ANIMATION_3);
		}
		vy = -SPEED_UP;
		TimeUp = GetTickCount();
	};
	~CardSelect() {};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		GameObject::Update(dt);
		y += dy;
		if (GetTickCount() - TimeUp > TIME_UP) {
			isDead = true;
			canDel = true;
		}
	}
	void Render()
	{
		CurAnimation->Render(x, y);

	}
};