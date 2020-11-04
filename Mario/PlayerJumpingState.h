#pragma once
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	void Render() {};
	PlayerJumpingState();
	~PlayerJumpingState();
};
