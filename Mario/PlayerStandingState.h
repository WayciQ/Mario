#pragma once
#include "PlayerState.h"
class PlayerStandingState : public PlayerState
{
public:
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerStandingState();
	~PlayerStandingState();

};

