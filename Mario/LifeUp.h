#pragma once
#pragma once
#include "Effect.h"
#define ANIMATION 90052
#define TIME_UP 300
#define SPEED_UP 0.5f
class LifeUp : public Effect
{
	DWORD TimeUp;
public:
	LifeUp() {
		CurAnimation = Animations::GetInstance()->Get(ANIMATION);
		vy = -SPEED_UP;
		TimeUp = GetTickCount();
	};
	~LifeUp() {}; 
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		GameObject::Update(dt);
		y += dy;
		if (GetTickCount() - TimeUp > TIME_UP) {
			isDead = true;
			canDel = true;
		}
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Render()
	{
		CurAnimation->Render(x, y);
	}
};