#pragma once
#include "PlayerState.h"
#include "CheckPoint.h"
class PlayerWorlMapState : public PlayerState
{
	int posX,posY;
	int move;
public:
	PlayerWorlMapState(int move);
	~PlayerWorlMapState();
	void Update(DWORD dt);
	void Render() {};
	void HandleKeyBoard();
};

