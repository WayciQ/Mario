#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerWhippingState.h"
void PlayerJumpingState::Update()
{
	if (player->vy >= 0)
	{
		player->ChangeAnimation(new PlayerFallingState());
		return;
	}
	this->HandleKeyBoard();
}

void PlayerJumpingState::HandleKeyBoard()
{
	
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->vx = player->speedJump;
		if (player->vx == 0) {
			player->vx = MARIO_WALKING_SPEED;
		}
	}
	else if (keyCode[DIK_LEFT])
	{
		player->nx = -1;
		player->vx = player->speedJump;
		if (player->vx == 0) {
			player->vx = -MARIO_WALKING_SPEED;
		}
	}
}

PlayerJumpingState::PlayerJumpingState()
{
	if (player->level == RACCOON) {
		player->Allow[WHIPPING] = true;
	}
	else
		player->Allow[WHIPPING] = false;

	if (!player->isJumping)
		player->vy = -MARIO_JUMP_SPEED_Y;
	player->isJumping = true;
	if (player->nx > 0)
		stateName = JUMPING_RIGHT;
	else
		stateName = JUMPING_LEFT;

	if (player->isSitting)
	{
		if (player->nx > 0)
			stateName = SITTING_RIGHT;
		else
			stateName = SITTING_LEFT;
	}
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
}

PlayerJumpingState::~PlayerJumpingState()
{
}