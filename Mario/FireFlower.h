#pragma once
#include "Item.h"
class FireFlower : public Item
{
	bool isRespawn;
	float posY;
public:
	FireFlower(float x, float y);
	~FireFlower() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render() {
		CurAnimation->Render(x, y);
		RenderBoundingBox();
	}
};

