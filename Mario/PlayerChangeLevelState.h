#pragma once
#include "PlayerState.h"
class PlayerChangeLevelState : public PlayerState
{
	bool isChangeState;
	int upsize;
	TYPE level;
public:
	PlayerChangeLevelState(bool isHurt,TYPE typeChange = BIG);
	void Render() {};
	~PlayerChangeLevelState() {};
	void Update(DWORD dt);
	void HandleKeyBoard();
};

