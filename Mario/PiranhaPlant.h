#pragma once
#include "Enemy.h"

class PiranhaPlant: public Enemy
{
	int startTimeUp;
	float PosX, PosY;
	float YY;
	bool upDone;
	bool isUp;
	bool isDown;
public:
	PiranhaPlant(TYPE type, float posx,float posy);
	~PiranhaPlant() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) ;
	void SetState(STATEOBJECT state);
	void UpdatePosition(DWORD dt) ;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Render();
};

