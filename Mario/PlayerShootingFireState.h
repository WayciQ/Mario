#pragma once
#include "PlayerState.h"
class PlayerShootingFireState : public PlayerState
{
public:
	PlayerShootingFireState();
	~PlayerShootingFireState();
	void Render();
	void Update(DWORD dt);
	void HandleKeyBoard();

};

