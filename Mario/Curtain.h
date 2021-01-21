#pragma once
#include "Effect.h"
#define ANIMATION 100002
#define	HEIGHT_CURTAIN 560
#define	SPEED_UP_CURTAIN 0.5f
class Curtain : public Effect
{
	DWORD TimeUp;
public:
	Curtain() {
		SetBBox(UNIT_GAME, HEIGHT_CURTAIN);
		CurAnimation = Animations::GetInstance()->Get(ANIMATION);
		vy = -SPEED_UP_CURTAIN;
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

