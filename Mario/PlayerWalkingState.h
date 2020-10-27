#pragma once

#include "PlayerState.h"

class PlayerWalkingState : public PlayerState
{
public:
	virtual void Update();
	virtual void HandleKeyBoard();
	PlayerWalkingState();
	~PlayerWalkingState();
};

