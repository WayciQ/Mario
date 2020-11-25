#include "PlayerJumpingShortState.h"
#include "PlayerFallingState.h"
#include "Mario.h"
PlayerJumpingShortState::PlayerJumpingShortState()
{
	player->Allow[JUMPING] = false;
	
	if (!player->isJumping)
	{
		player->vy = -MARIO_JUMP_SPEED_Y;
	}
	
	if (!player->canFallJump)
	{
		player->vy = -MARIO_JUMP_SPEED_Y;
	}

	player->isJumping = true;

	if (player->nx > 0)
	{
		stateName = JUMPING_RIGHT;
	}
	else
	{
		stateName = JUMPING_LEFT;
	}

		
	
}
void PlayerJumpingShortState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	
	if (player->vy >= 0)
	{
		player->curY = player->y;
		player->ChangeAnimation(new PlayerFallingState());
	}
}
void PlayerJumpingShortState::HandleKeyBoard()
{
	if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{

	}
}
PlayerJumpingShortState::~PlayerJumpingShortState(){}

