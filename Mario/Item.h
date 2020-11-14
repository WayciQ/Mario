#pragma once
#include "GameObject.h"
class Item : public GameObject
{
	Animation* CurAnimation;
public:
	Item() {
		tag = ITEM;
		isDead = false;
	};
	~Item() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(float dt) {};
	virtual void Render() {
		CurAnimation->Render(x, y, 255);
		RenderBoundingBox();
	};
	virtual void Revival() {};
};

