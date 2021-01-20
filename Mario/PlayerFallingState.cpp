#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerFlyingState.h"
#include "PlayerRaccoonJumpTail.h"
PlayerFallingState::PlayerFallingState()
{
	//DebugOut(L"[info] FALLING: vx: %f\n", player->vx);
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	player->Allow[JUMPING] = false;
	player->isJumpDone = true;
	//player->isFalling = true;
	player->isOnSky = true;
	switch (player->level)
	{
	case SMALL:
		player->Allow[SITTING] = false;
		break;
	case BIG:
		break;
	case RACCOON:
		player->Allow[RACCON_WHIPING_FLY] = true;
		player->Allow[WHIPPING] = true;
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
			player->Allow[RACCON_WHIPING_FLY] = false;
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
		if (player->vy == 0) {
			
			player->ChangeState(new PlayerStandingState());
		}
	}
	
}
void PlayerFallingState::HandleKeyBoard()
{
	if (keyCode[DIK_S] && player->Allow[FLYING] && player->isFlying)
	{
		if ((keyCode[DIK_RIGHT]))
		{
			player->nx = 1;
			player->ChangeState(new PlayerFlyingState());
		}
		else if ((keyCode[DIK_LEFT]))
		{
			player->nx = -1;
			player->ChangeState(new PlayerFlyingState());
		}
		else
		{
			player->ChangeState(new PlayerFlyingState());
		}
	}
	else if (keyCode[DIK_RIGHT] && player->isOnSky)
	{
		player->vx = player->vx > MARIO_WALKING_SPEED ? MARIO_WALKING_SPEED : player->vx + MARIO_INERTIA_WALKING;
		player->nx = 1;
		player->ChangeState(new PlayerFallingState());
	}
	else if (keyCode[DIK_LEFT] && player->isOnSky )
	{
		player->vx = player->vx < -MARIO_WALKING_SPEED ? -MARIO_WALKING_SPEED : player->vx - MARIO_INERTIA_WALKING;
		player->nx = -1;
		player->ChangeState(new PlayerFallingState());
	}
}

PlayerFallingState::~PlayerFallingState()
{
}
