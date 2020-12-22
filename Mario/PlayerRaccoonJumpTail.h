#pragma once
#include "PlayerState.h"
class PlayerRaccoonJumpTail : public PlayerState
{
	DWORD timeWaving;
public:
	PlayerRaccoonJumpTail();
	~PlayerRaccoonJumpTail();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render();
};

