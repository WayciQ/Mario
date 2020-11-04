#pragma once
#include "PlayerState.h"
class PlayerWhippingState : public PlayerState
{
public: 
	void Update();
	void HandleKeyBoard();
	void Render();
	PlayerWhippingState();
	~PlayerWhippingState();
};

