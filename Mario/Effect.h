#pragma once
#include "GameObject.h"
class Effect : public GameObject
{
public:
	Animation* CurAnimation;
	Effect() {
		tag = EFFECT;
	};
	~Effect() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
			
	};
	virtual void Render() {
		CurAnimation->Render(x, y);
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};

