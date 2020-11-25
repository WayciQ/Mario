#pragma once
#include "PlayerState.h"
class PlayerSittingState : public PlayerState
{
public:
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerSittingState();
	~PlayerSittingState();
};