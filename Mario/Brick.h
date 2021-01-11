#pragma once
#include "GameObject.h"

#define BRICK_DEFLECT_SPEED 3
class Brick : public GameObject
{
	
public:
	bool isSpawnItem;
	Animation* CurAnimation;
	Brick();
	~Brick() {};
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void ChangeAnimation(STATEOBJECT state);
};

