#pragma once
#include "PlayerState.h"
class PlayerSittingState : public PlayerState
{
public:
	virtual void Update();
	virtual void HandleKeyBoard();
	PlayerSittingState();
	~PlayerSittingState();
};