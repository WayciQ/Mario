#include "PlayerJumpingShortState.h"
#include "PlayerFallingState.h"
#include "Mario.h"
PlayerJumpingShortState::PlayerJumpingShortState()
{
	player->Allow[JUMPING_LONG] = false;
	
	if (!player->isJumping)
	{
		player->vy = -MARIO_JUMP_SPEED_Y;
	}
	
	if (!player->canFallJump)
	{
		player->vy = -MARIO_JUMP_SPEED_Y;
	}

	player->isJumping = true;
	if (player->canFly)
	{
		if (player->nx > 0)
			stateName = FLYING_RIGHT;
		else
			stateName = FLYING_LEFT;
	}
	
	else
	{
		if (player->nx > 0)
		{
			stateName = JUMPING_RIGHT;
		}
		else
		{
			stateName = JUMPING_LEFT;
		}
	}
}
void PlayerJumpingShortState::Update()
{
	this->HandleKeyBoard();
	
	if (player->vy >= 0)
	{
		player->ChangeAnimation(new PlayerFallingState());
	}
}
void PlayerJumpingShortState::HandleKeyBoard()
{
	
}
PlayerJumpingShortState::~PlayerJumpingShortState(){}

