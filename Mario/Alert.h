#pragma once
#include "GameObject.h"
class Alert : public GameObject
{
public:
	STATEOBJECT card;
	RECT r;
	DWORD startTimeAlert;
	ID3DXFont* font;
	Alert(STATEOBJECT card, float x, float y);
	~Alert() {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)  ;
	void DrawTitle(string alert);
	void DrawtImage(STATEOBJECT sp);
	void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};

}; 
