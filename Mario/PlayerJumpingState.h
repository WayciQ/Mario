#pragma once
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	PlayerJumpingState();
	~PlayerJumpingState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};
