#include "PlayerLastRunState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
PlayerLastRunState::PlayerLastRunState() {
	
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
void PlayerLastRunState::Update() {
	if (!player->isWaittingPressBtn)
	{
		player->isWalkingComplete = false;
		player->ChangeAnimation(new PlayerStandingState());
		return;
	}
	this->HandleKeyBoard();
}