#pragma once
#include "PlayerState.h"
class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState();
	~PlayerStandingState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};

