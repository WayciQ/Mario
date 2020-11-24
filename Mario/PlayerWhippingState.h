#pragma once
#include "PlayerState.h"
class PlayerWhippingState : public PlayerState
{
public: 
	PlayerWhippingState();
	~PlayerWhippingState();
	void Update(DWORD dt);
	void HandleKeyBoard();
	void Render();
};

