#pragma once
#include "PlayerState.h"
class PlayerStandingState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	void Render() {};
	PlayerStandingState();
	~PlayerStandingState();

};

