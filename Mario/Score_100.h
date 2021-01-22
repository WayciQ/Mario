#pragma once
#pragma once
#pragma once
#include "Effect.h"
#define ANIMATION 90051
#define TIME_UP 300
#define SPEED_UP 0.5f
class Score_100 : public Effect
{
	DWORD TimeUp;
public:
	Score_100() {
		CurAnimation = Animations::GetInstance()->Get(ANIMATION);
		vy = -SPEED_UP;
		TimeUp = GetTickCount();
	};
	~Score_100() {};
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