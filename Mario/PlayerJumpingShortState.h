#pragma once
#include "PlayerState.h"
class PlayerJumpingShortState : public PlayerState
{
public: 
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerJumpingShortState();
	~PlayerJumpingShortState();
};

