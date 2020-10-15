#pragma once
#include "PlayerState.h"
class PlayerRunningState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	PlayerRunningState();
	~PlayerRunningState();
};

