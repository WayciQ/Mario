#pragma once
#include "PlayerState.h"
class PlayerDieState : public PlayerState
{
public:
	~PlayerDieState() {};
	PlayerDieState();
	void Render() {};
	void Update(DWORD dt);
	void HandleKeyBoard() {};
};

