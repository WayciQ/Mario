#pragma once
#include "GameGlobal.h"
class PlayerState
{
public:
	PlayerState() {};
	virtual void HandleKeyBoard() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	STATEPLAYER stateName; // animation by state;
};

