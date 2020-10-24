#pragma once
#include "PlayerState.h"
class PlayerWhippingFlyState	: public PlayerState
{
public: 
	virtual void Update();
	virtual void HandleKeyBoard();
	PlayerWhippingFlyState();
	~PlayerWhippingFlyState();
};

