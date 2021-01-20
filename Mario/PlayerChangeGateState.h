#pragma once
#include "PlayerState.h"
class PlayerChangeGateState : public PlayerState
{

	float startY;
	int waymove;
	bool isChangeDone;
	float posX, posY;
public:
	PlayerChangeGateState(int way, bool isIn,float x,float y);
	~PlayerChangeGateState() {};
	void Update(DWORD dt);
	void Render() {}
	void HandleKeyBoard();
};

