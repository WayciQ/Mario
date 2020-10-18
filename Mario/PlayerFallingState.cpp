#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
void PlayerFallingState::Update()
{
	if (!player->isJumping)
	{
		player->ChangeAnimation(new PlayerStandingState());
		return;
	}
	this->HandleKeyBoard();
}
void PlayerFallingState::HandleKeyBoard()
{

}

PlayerFallingState::PlayerFallingState()
{
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	if (player->nx > 0)
		stateName = FALLING_RIGHT;
	else
		stateName = FALLING_LEFT;
	if (player->isSitting)
	{
		if (player->nx > 0)
			stateName = SITTING_RIGHT;
		else
			stateName = SITTING_LEFT;
	}
}


PlayerFallingState::~PlayerFallingState()
{
}
