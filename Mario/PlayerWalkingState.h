#pragma once

#include "PlayerState.h"

class PlayerWalkingState : public PlayerState
{
public:
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerWalkingState();
	~PlayerWalkingState();
};

