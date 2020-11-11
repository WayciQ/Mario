#pragma once
#include "Enemy.h" 
class NipperPlant : public Enemy
{
	int startTimeUp;
	float PosX, PosY;
	bool isUp;
public:
	NipperPlant(TYPE type,float x, float y);
	~NipperPlant() {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void UpdatePosition(DWORD dt);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();

};

