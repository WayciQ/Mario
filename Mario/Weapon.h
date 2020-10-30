#pragma once
#include "GameObject.h"

class Weapon: public GameObject
{
public:
	Weapon();
	~Weapon() {};
	virtual void SetBBox(float w, float h) { this->widthBBox = w; this->heightBBox = h; }
	Animation* CurAnimation;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void UpdatePosititon(DWORD dt) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void CollisonGroundWall(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render();

};