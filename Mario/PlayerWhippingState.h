#pragma once
#include "PlayerState.h"
class PlayerWhippingState : public PlayerState
{
public: 
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render();
	PlayerWhippingState();
	~PlayerWhippingState();
};

