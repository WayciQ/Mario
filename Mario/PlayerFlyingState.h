#pragma once
#include "PlayerState.h"
class PlayerFlyingState : public PlayerState
{
public:
	PlayerFlyingState();
	~PlayerFlyingState() {};
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};

