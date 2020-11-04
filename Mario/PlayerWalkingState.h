#pragma once

#include "PlayerState.h"

class PlayerWalkingState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	void Render() {};
	PlayerWalkingState();
	~PlayerWalkingState();
};

