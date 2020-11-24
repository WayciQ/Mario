#pragma once
#include "PlayerState.h"
class PlayerHoldingState : public PlayerState
{
public:
	PlayerHoldingState();
	~PlayerHoldingState() {};
	void Update(DWORD dt);
	void HandleKeyBoard();
};

