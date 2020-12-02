#pragma once
#include "GameGlobal.h"
#include "Sprites.h"
class ScoreBoard
{
	static ScoreBoard* __instance;
	ID3DXFont* font;
	RECT rect;
	string information;
	LPSPRITE Item1;
	LPSPRITE Item2;
	LPSPRITE Item3;
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
	~ScoreBoard() {
	};

};

