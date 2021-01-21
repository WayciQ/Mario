#pragma once
#include "Effect.h"
#define ANIMATION 100002
class Curtain : public Effect
{
	DWORD TimeUp;
public:
	Curtain() {
		SetBBox(UNIT_GAME, 560);
		CurAnimation = Animations::GetInstance()->Get(ANIMATION);
		vy = -0.5;
		TimeUp = GetTickCount();
	}
	~Curtain() {
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		GameObject::Update(dt);
		y += dy;
		if (GetTickCount() - TimeUp >= 2000) {
			isDead = true;
			canDel = true;
		}
	}
	void Render() {
		CurAnimation->Render(x, y);
	}
};

