#pragma once
#include "PlayerState.h"
class PlayerDieState : public PlayerState
{
public:
	PlayerDieState();
	~PlayerDieState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render();
};

