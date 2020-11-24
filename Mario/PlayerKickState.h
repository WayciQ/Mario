#pragma once
#include "PlayerState.h"
class PlayerKickState : public PlayerState
{
public:
	PlayerKickState();
	~PlayerKickState(){}
	void Render();
	void Update(DWORD dt);
	void HandleKeyBoard();
};

