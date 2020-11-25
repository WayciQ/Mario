#pragma once
#include "PlayerState.h"
class PlayerLastRunState : public PlayerState
{
public:
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
	PlayerLastRunState();
	~PlayerLastRunState();
};

