#pragma once
#include "PlayerState.h"

class PlayerFallingState : public PlayerState
{
public:
	virtual void Update();
	virtual void HandleKeyBoard();
	PlayerFallingState();
	~PlayerFallingState();
};


