#pragma once
#include "GameGlobal.h"
class PlayerState
{
public:
	PlayerState() {};
	virtual void HandleKeyBoard() = 0;
	virtual void Update() = 0;
	STATENAME stateName;
	STATENAME PrevState;
};

