#include "PlayerLastRunState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
PlayerLastRunState::PlayerLastRunState() {
	//DebugOut(L"[info] LASTRUN: vx: %f\n", player->vx);
	
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

	

	if (player->vx < MARIO_INERTIA_WALKING && player->vx > -MARIO_INERTIA_WALKING)
	{
		player->vx = 0;
	}
	else
	{
		if (player->vx > 0)
		{
			player->vx = player->vx < 0 ? 0 : player->vx - MARIO_INERTIA_WALKING;
		}
		else
		{
			player->vx = player->vx > 0 ? 0 : player->vx + MARIO_INERTIA_WALKING;

		}
	}
	if (!player->isWaittingPressBtn && player->vx == 0)
	{
		player->isWalkingComplete = false;
		player->ChangeState(new PlayerStandingState());
	}
}