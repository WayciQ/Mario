#pragma once
#include "PlayerState.h"

class PlayerFallingState : public PlayerState
{
public:
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerFallingState();
	~PlayerFallingState();
};


