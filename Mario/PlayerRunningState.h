#pragma once
#include "PlayerState.h"
class PlayerRunningState : public PlayerState
{
public:
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerRunningState();
	~PlayerRunningState();
};

