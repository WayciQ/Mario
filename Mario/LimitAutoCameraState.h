#pragma once
#include "PlayerState.h"
class LimitAutoCameraState : public PlayerState
{
public:
	LimitAutoCameraState();
	~LimitAutoCameraState() {};
	void Update(DWORD dt);
	void Render();
	void HandleKeyBoard();
};

