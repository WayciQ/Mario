#pragma once
#include "PlayerState.h"
class PlayerSittingState : public PlayerState
{
public:
	void Update();
	void HandleKeyBoard();
	void Render() {};
	PlayerSittingState();
	~PlayerSittingState();
};