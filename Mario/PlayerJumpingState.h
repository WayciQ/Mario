#pragma once
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	virtual void Update();
	virtual void HandleKeyBoard();
	PlayerJumpingState();
	~PlayerJumpingState();
};
