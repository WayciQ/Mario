#pragma once
#include "PlayerState.h"
class PlayerWhippingState : public PlayerState
{
public: 
	virtual void Update();
	virtual void HandleKeyBoard();
	PlayerWhippingState();
	~PlayerWhippingState();
};

