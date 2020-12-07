#pragma once
#include "PlayerState.h"
class PlayerChangeLevelState : public PlayerState
{
	bool isBig;
	bool upsize;
public:
	PlayerChangeLevelState(bool isdead,TYPE typeChange = BIG);
	void Render() {};
	~PlayerChangeLevelState() {};
	void Update(DWORD dt);
	void HandleKeyBoard() {};
};

