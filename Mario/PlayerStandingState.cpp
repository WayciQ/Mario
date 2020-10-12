#include "PlayerStandingState.h"
#include "PlayerState.h"
#include "Mario.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "PlayerWhippingState.h"
PlayerStandingState::PlayerStandingState() {
	player->allow[JUMPING] = true;
	player->allow[WALKING] = true;
	if (player->level == SMALL) {
		player->allow[WHIPPING] = false;
		player->allow[SITTING] = false;
	}
	else if (player->level == BIG)
	{
		player->allow[WHIPPING] = false;
		player->allow[SITTING] = true;
	}
	else {
		player->allow[WHIPPING] = true;
		player->allow[SITTING] = true;
	}
	
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	player->vx = 0;
	//player->nx = 1;
	player->isWhipping = false;
	player->isSitting = false;
	player->isJumping = false;
	if (player->nx > 0)
		stateName = STANDING_RIGHT;
	else stateName = STANDING_LEFT;
	
}

void PlayerStandingState::HandleKeyBoard() {

	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT])
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
			player->ChangeAnimation(new PlayerWalkingState());
	}
	else if (keyCode[DIK_DOWN] && player->allow[SITTING])
	{
		player->ChangeAnimation(new PlayerSittingState());
	}
	
}

void PlayerStandingState::Update()
{
	this->HandleKeyBoard();
}

PlayerStandingState::~PlayerStandingState()
{
}

