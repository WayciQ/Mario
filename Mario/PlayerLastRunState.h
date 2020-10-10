#pragma once
#include "PlayerState.h"
class PlayerLastRunState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	PlayerLastRunState();
	~PlayerLastRunState();
};

