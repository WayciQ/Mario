#pragma once

#include "PlayerState.h"

class PlayerWalkingState : public PlayerState
{
public:
	PlayerWalkingState();
	~PlayerWalkingState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};

