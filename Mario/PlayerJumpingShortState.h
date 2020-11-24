#pragma once
#include "PlayerState.h"
class PlayerJumpingShortState : public PlayerState
{
public: 
	PlayerJumpingShortState();
	~PlayerJumpingShortState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};

