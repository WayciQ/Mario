#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerFlyingState.h"

PlayerFallingState::PlayerFallingState()
{
	//DebugOut(L"[info] FALLING: vx: %f\n", player->vx);
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	player->Allow[JUMPING] = false;
	player->Allow[JUMPING_SHORT] = false;
	player->isJumpingShort = false;
	switch (player->level)
	{
	case SMALL:
		player->Allow[SITTING] = false;
		break;
	case BIG:
		break;
	case RACCOON:
		player->Allow[WHIPPING] = true;
		player->Allow[JUMPING_SHORT] = true;
		break;
	case FIRE:
		player->Allow[FIRING_FIRE] = true;
		break;
	}

	if (player->isPicking)
	{
		if (player->nx > 0)
		{
			stateName = PICKING_RIGHT;
		}
		else stateName = PICKING_LEFT;
	}
	else 
	{
		if (player->isFlying)
		{
			if (player->nx > 0)
				stateName = FLYING_FALL_RIGHT;
			else
				stateName = FLYING_FALL_LEFT;
		}
		else
		{
			if (player->nx > 0)
				stateName = FALLING_RIGHT;
			else
				stateName = FALLING_LEFT;
			/*if (player->Allow[JUMPING_SHORT] && player->isJumpingShort)
			{
				if (player->nx > 0)
					stateName = RACCON_WHIPING_FLY_RIGHT;
				else
					stateName = RACCON_WHIPING_FLY_LEFT;
			}*/
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
	if (!player->isOnSky)
	{
		if(player->vy == 0)
			player->ChangeAnimation(new PlayerStandingState());
	}
	
}
void PlayerFallingState::HandleKeyBoard()
{
	if (keyCode[DIK_S] && player->Allow[FLYING] && player->isFlying)
	{
		if ((keyCode[DIK_RIGHT]))
		{
			player->vx = MARIO_WALKING_SPEED;
			player->nx = 1;
			player->ChangeAnimation(new PlayerFlyingState());
		}
		else if ((keyCode[DIK_LEFT]))
		{
			player->vx = -MARIO_WALKING_SPEED;
			player->nx = -1;
			player->ChangeAnimation(new PlayerFlyingState());
		}
		else
		{
			player->ChangeAnimation(new PlayerFlyingState());
		}
	}
	else if (keyCode[DIK_RIGHT])
	{
		player->nx = 1;
		player->vx = MARIO_WALKING_SPEED;
		player->ChangeAnimation(new PlayerFallingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		player->nx = -1;
		player->vx = -MARIO_WALKING_SPEED;
		player->ChangeAnimation(new PlayerFallingState());
	}
	
}

PlayerFallingState::~PlayerFallingState()
{
}
