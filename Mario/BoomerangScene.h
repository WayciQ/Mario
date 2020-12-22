#pragma once
#include "Enemy.h"
class BoomerangScene : public Enemy
{
	float maxLeft;
	float maxRight;
public:
	BoomerangScene() {
		widthBBox = heightBBox = 16;
		type = BOOMERANG;
		CurAnimation = animationsSets->Get(BOOMERANG)->Get(ENEMY_WALKING_RIGHT);
		vx = 0.02f;
	}
	~BoomerangScene() {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		//GameObject::Update(dt);
		vector<LPGAMEOBJECT> coEvents;
		coEvents.clear();
		UpdatePosition(dt);
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (IsCollisionAABB(GetRect(), coObjects->at(i)->GetRect()))
			{
				maxLeft = coObjects->at(i)->x;
				maxRight = coObjects->at(i)->x + widthBBox;
			}
		}
		
	};
	void UpdatePosition(DWORD dt) {
		if (x < maxLeft) {
			vx = 0.02f;
			CurAnimation = animationsSets->Get(BOOMERANG)->Get(ENEMY_WALKING_RIGHT);
		}
		else if(x > maxRight){
		vx = -0.02f;
		CurAnimation = animationsSets->Get(BOOMERANG)->Get(ENEMY_WALKING_LEFT);
		}
		x += dx;
		GameObject::Update(dt);
	};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	};
	void Render()
	{
		CurAnimation->Render(x, y, 255);
	}
};

