#pragma once
#include "PlayerState.h"
class PlayerHoldingState : public PlayerState
{
public:
	PlayerHoldingState();
	~PlayerHoldingState() {};
	void Update();
	void HandleKeyBoard();
};

