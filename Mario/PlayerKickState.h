#pragma once
#include "PlayerState.h"
class PlayerKickState : public PlayerState
{
public:
	PlayerKickState();
	~PlayerKickState(){}
	virtual void Update();
	virtual void HandleKeyBoard();
};

