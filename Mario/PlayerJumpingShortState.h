#pragma once
#include "PlayerState.h"
class PlayerJumpingShortState : public PlayerState
{
public: 
	virtual void Update();
	virtual void HandleKeyBoard();
	void Render() {};
	PlayerJumpingShortState();
	~PlayerJumpingShortState();
};
