#pragma once
#include "PlayerState.h"

class PlayerFallingState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	PlayerFallingState();
	~PlayerFallingState();
};


