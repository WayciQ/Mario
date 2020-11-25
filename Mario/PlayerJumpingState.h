#pragma once
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerJumpingState();
	~PlayerJumpingState();
};
