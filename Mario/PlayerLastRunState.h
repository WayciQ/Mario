#pragma once
#include "PlayerState.h"
class PlayerLastRunState : public PlayerState
{
public:
	PlayerLastRunState();
	~PlayerLastRunState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render() {};
};

