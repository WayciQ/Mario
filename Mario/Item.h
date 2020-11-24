#pragma once
#include "GameObject.h"
class Item : public GameObject
{

public:
	Animation* CurAnimation;
	Item(float x,float y) {
		SetPosition(x, y);
		tag = ITEM;
		isDead = false;
	};
	~Item() {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void UpdatePosition(float dt) {};
	virtual void Render() {
		CurAnimation->Render(x, y, 255);
		RenderBoundingBox();
	};
	virtual void Revival() {};
};

