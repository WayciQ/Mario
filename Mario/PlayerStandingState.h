#pragma once
#include "PlayerState.h"
class PlayerStandingState : public PlayerState
{
public:
	virtual void Update();
	virtual void HandleKeyBoard();
	PlayerStandingState();
	~PlayerStandingState();

};

