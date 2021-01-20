#pragma once
#include "Sprites.h"
#include "Animations.h"
class HUB
{
	static HUB* __instance;
	ID3DXFont* font;
	RECT rect;
	string information;
	Animation* Item1;
	Animation* Item2;
	Animation* Item3;
	LPSPRITE typePlayer;
	LPSPRITE hub;
	LPSPRITE speed;
	int NumSpeed;
	Animation* push;
	bool isDrawPush;
public:
	
	static HUB* GetInstance();
	HUB();
	void Init();
	void Update(float dt);
	void Render();
	~HUB() {};

};

