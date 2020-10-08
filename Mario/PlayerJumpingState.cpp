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
	
}

PlayerJumpingState::PlayerJumpingState()
{
	
	player->allow[JUMPING] = false;
	player->allow[WHIPPING] = true;
	if (!player->isJumping)
		player->vy = -MARIO_JUMP_SPEED_Y;
	player->isJumping = true;
	if (player->nx > 0)
		stateName = JUMPING_RIGHT;
	else
		stateName = JUMPING_LEFT;
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
}

PlayerJumpingState::~PlayerJumpingState()
{
}