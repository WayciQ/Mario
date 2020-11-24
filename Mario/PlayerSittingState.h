#pragma once
#include "PlayerState.h"
class PlayerSittingState : public PlayerState
{
public:
	PlayerSittingState();
	~PlayerSittingState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};