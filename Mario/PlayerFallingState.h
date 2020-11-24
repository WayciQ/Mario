#pragma once
#include "PlayerState.h"

class PlayerFallingState : public PlayerState
{
public:
	PlayerFallingState();
	~PlayerFallingState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};


