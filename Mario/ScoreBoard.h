#pragma once
#include "Sprites.h"
#include "Animations.h"
class ScoreBoard
{
	static ScoreBoard* __instance;
	ID3DXFont* font;
	RECT rect;
	string information;
	Animation* Item1;
	Animation* Item2;
	Animation* Item3;
	LPSPRITE typePlayer;
	LPSPRITE HUB;
	LPSPRITE speed;
	int NumSpeed;
	LPSPRITE push;
	bool isDrawPush;
public:
	
	static ScoreBoard* GetInstance();
	ScoreBoard();
	void Init();
	void Update(float dt);
	void Render();
	~ScoreBoard() {};

};

