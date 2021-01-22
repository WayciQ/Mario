#pragma once
#include "GameObject.h"
class Alert : public GameObject
{
public:
	RECT rect;
	DWORD startTimeAlert;
	ID3DXFont* test;
	string infor;
	Animation* Item;
	DWORD TimeUP;
	bool isShow;
	bool isShowCard;
	Alert(STATEOBJECT card, float x, float y);
	~Alert();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Init();
	void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};

}; 
