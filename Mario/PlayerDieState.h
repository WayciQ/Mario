#pragma once
#include "PlayerState.h"
class PlayerDieState : public PlayerState
{
public:
	PlayerDieState();
	void Render() {};
	~PlayerDieState() {};
	void Update(DWORD dt);
	void HandleKeyBoard() {};
};

