#pragma once
#include "Brick.h"
class BlockMove : public Brick
{
public:
	BlockMove(float w, float h);
	~BlockMove();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void UpdatePosition(DWORD dt) {};
	void Render();
};

