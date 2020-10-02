#include "PlayerStandingState.h"
#include "PlayerState.h"
#include "Mario.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
PlayerStandingState::PlayerStandingState() {
	player->allow[JUMPING] = true;
	player->allow[SITTING] = true;
	player->allow[WALKING] = true;
	player->stateBoundingBox == MARIO_STATE_BIG_BOUNDING_BOX;
	player->vx = 0;
	//player->nx = 1;
	player->isSitting = false;
	player->isJumping = false;

	if (player->nx > 0)
		stateName = STADING_RIGHT;
	else stateName = STANDING_LEFT;
	
}

void PlayerStandingState::HandleKeyBoard() {

	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT])
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		DebugOut(L"b");
		player->ChangeAnimation(new PlayerWalkingState());
	}
	else if (keyCode[DIK_DOWN])
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

