#pragma once
#include "GameObject.h"
#define SPEED_X 0.15f
#define ANIMATION_BREAKBRICK 817
#define TIME_DEL 700
class BreakBrick : public GameObject
{
	DWORD timeDead;
public:
	Animation* CurAnimation;
	BreakBrick(int nx, float vy) {
		CurAnimation = Animations::GetInstance()->Get(ANIMATION_BREAKBRICK);
		this->nx = nx;
		timeDead = GetTickCount();
		bool isSpawnItem;
		this->vy = vy;
		vx = nx > 0 ? SPEED_X : -SPEED_X;
	};
	~BreakBrick() {};
	void Render() {
		CurAnimation->Render(x, y);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		GameObject::Update(dt);
		vy += WORLD_GRAVITY * dt;
		y += dy;
		x += dx;
		
		if (GetTickCount() - timeDead >= TIME_DEL)
		{
			isDead = true;
		}

		if (isDead)
		{
			canDel = true;
		}
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom){}
};

