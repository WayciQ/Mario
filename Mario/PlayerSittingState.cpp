#include "PlayerSittingState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"

PlayerSittingState::PlayerSittingState()
{
	player->Allow[JUMPING] = true;
	player->Allow[WALKING] = false;
	player->Allow[WHIPPING] = false;
	player->isSitWalk = true;
	player->isSitting = true;
	player->stateBoundingBox = MARIO_STATE_BIG_SIT_BOUNDING_BOX;
	if (player->nx > 0) {
		stateName = SITTING_RIGHT;
	}
	else stateName = SITTING_LEFT;
}

void PlayerSittingState::Update()
{
	if (!player->isSitting) {
		player->ChangeAnimation(new PlayerStandingState());
		return;
	}
	this->HandleKeyBoard();
}
void PlayerSittingState::HandleKeyBoard()
{
	if (keyCode[DIK_DOWN]) 
	{
		if ((keyCode[DIK_LEFT] || keyCode[DIK_RIGHT]) )
		{
		
			player->ChangeAnimation(new PlayerWalkingState());
		}
	}
	else {
		player->ChangeAnimation(new PlayerStandingState());
	}
}
	
PlayerSittingState::~PlayerSittingState() {

}