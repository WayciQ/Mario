#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"


PlayerFallingState::PlayerFallingState()
{
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	if (player->canFly)
	{
		if (player->nx > 0)
			stateName = FLY_FALL_RIGHT;
		else
			stateName = FLY_FALL_LEFT;
		
	}
	else
	{
		if (player->nx > 0)
			stateName = FALLING_RIGHT;
		else
			stateName = FALLING_LEFT;
	}
	
	if (player->isSitting)
	{
		if (player->nx > 0)
			stateName = SITTING_RIGHT;
		else
			stateName = SITTING_LEFT;
	}
}
void PlayerFallingState::Update()
{
	this->HandleKeyBoard();
	if (!player->isJumping)
	{
		player->canFly = false;
		player->ChangeAnimation(new PlayerStandingState());
	}
	
}
void PlayerFallingState::HandleKeyBoard()
{

}

PlayerFallingState::~PlayerFallingState()
{
}
