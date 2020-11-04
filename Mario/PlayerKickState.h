#pragma once
#include "PlayerState.h"
class PlayerKickState : public PlayerState
{
public:
	PlayerKickState();
	~PlayerKickState(){}
	void Render();
	virtual void Update();
	virtual void HandleKeyBoard();
};

