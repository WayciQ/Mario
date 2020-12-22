#pragma once
#include "PlayerState.h"
class PlayerEndSceneState : public PlayerState
{
	DWORD startTime;
public:
	PlayerEndSceneState();
	~PlayerEndSceneState() {}
	void Update(DWORD dt);
	void HandleKeyBoard() {};
	void Render() {}
};

