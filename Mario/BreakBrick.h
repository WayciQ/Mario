#pragma once
#include "GameObject.h"
#define SPEED_X 0.02
class BreakBrick : public GameObject
{
public:
	Animation* CurAnimation;
	BreakBrick(int nx, float vy,float x,float y) {
		CurAnimation = Animations::GetInstance()->Get(808);
		this->nx = nx;
		this->vy = vy;
	};
	~BreakBrick() {};
	void Render() {
		CurAnimation->Render(x, y);
	}
	void Update(DWORD dt)
	{
		GameObject::Update(dt);
		vy += WORLD_GRAVITY * dt;
		y += dy;
		vx = nx > 0 ? SPEED_X : -SPEED_X;

		if (isDead)
		{
			canDel = true;
		}
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom){}
};

