#pragma once
#include "PlayerState.h"
class PlayerShootingFireState : public PlayerState
{
public:
	PlayerShootingFireState();
	~PlayerShootingFireState();
	virtual void Update();
	virtual void HandleKeyBoard();

};

