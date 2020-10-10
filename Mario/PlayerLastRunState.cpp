#include "PlayerLastRunState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
PlayerLastRunState::PlayerLastRunState() {
	
	player->vx = 0;
	if (player->walkingDirection > 0) {
		stateName = LAST_LEFT;
	}
	else {
		stateName = LAST_RIGHT;
	}
}
PlayerLastRunState::~PlayerLastRunState(){}
void PlayerLastRunState::HandleKeyBoard() {
	/*if (keyCode[DIK_LEFT])
	{
		player->nx = -1;
		player->ChangeAnimation(new PlayerWalkingState());
	}
	else if (keyCode[DIK_RIGHT])
	{
		player->nx = 1;
		player->ChangeAnimation(new PlayerWalkingState());
	}*/
	
}
void PlayerLastRunState::Update() {
	if (!player->isWaittingPress)
	{
		player->isWalkingComplete = false;
		player->ChangeAnimation(new PlayerStandingState());
		return;
	}
	this->HandleKeyBoard();
}