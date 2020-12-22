#include "PlayerLastRunState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
PlayerLastRunState::PlayerLastRunState() {
	//DebugOut(L"[info] LASTRUN: vx: %f\n", player->vx);
	player->vx = 0;
	if (player->walkingDirection > 0) {
		stateName = LAST_RIGHT;
	}
	else {
		stateName = LAST_LEFT;
	}
}
PlayerLastRunState::~PlayerLastRunState(){}
void PlayerLastRunState::HandleKeyBoard() {
}
void PlayerLastRunState::Update(DWORD dt) {

	if (!player->isWaittingPressBtn)
	{
		player->isWalkingComplete = false;
		player->ChangeState(new PlayerStandingState());
		return;
	}
}