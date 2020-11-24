#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingShortState.h"

PlayerFallingState::PlayerFallingState()
{
	
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	player->Allow[JUMPING_LONG] = false;
	player->Allow[JUMPING_SHORT] = false;
	switch (player->level)
	{
	case SMALL:
		player->Allow[SITTING] = false;
		break;
	case BIG:
		break;
	case RACCOON:
		player->Allow[JUMPING_SHORT] = true;
		player->Allow[WHIPPING] = true;
		break;
	case FIRE:
		player->Allow[FIRING_FIRE] = true;
		break;
	}

	if (player->isHolding)
	{
		if (player->nx > 0)
		{
			stateName = PICKING_RIGHT;
		}
		else stateName = PICKING_LEFT;
	}
	else 
	{
		if (player->canFly)
		{
			if (player->nx > 0)
				stateName = FLYING_FALL_RIGHT;
			else
				stateName = FLYING_FALL_LEFT;
		}
		else if (player->canShortJump)
		{

			if (player->nx > 0)
				stateName = RACCON_WHIPING_FLY_RIGHT;
			else
				stateName = RACCON_WHIPING_FLY_LEFT;
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
	
}
void PlayerFallingState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	if (!player->isJumping)
	{
		player->canFly = false;
		player->canShortJump = false;
		player->canFallJump = true;
		if(player->vy == 0)
			player->ChangeAnimation(new PlayerStandingState());
	}
	
}
void PlayerFallingState::HandleKeyBoard()
{
	if (player->level == RACCOON && player->Allow[JUMPING_SHORT])
	{
		if (!player->Allow[FLYING_PUSH])
		{
			if (keyCode[DIK_S] && player->isJumping && player->canFallJump)
			{

				player->canShortJump = false;
				player->canFallJump = false;
				player->ChangeAnimation(new PlayerJumpingShortState());
			}
			else
				if (keyCode[DIK_X] && player->isJumping)
				{			
					player->vy = 0;
					player->canShortJump = true;
					player->ChangeAnimation(new PlayerFallingState());
				}
		}
		
	}
	
}

PlayerFallingState::~PlayerFallingState()
{
}
