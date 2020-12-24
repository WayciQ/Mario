#pragma once
#include "PlayerState.h"
class PlayerRaccoonJumpTail : public PlayerState
{
public:
	PlayerRaccoonJumpTail();
	~PlayerRaccoonJumpTail();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render();
};

