#pragma once
#include "PlayerState.h"
class PlayerWalkingLastState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	PlayerWalkingLastState();
	~PlayerWalkingLastState();
};

