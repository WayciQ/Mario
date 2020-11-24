#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSittingState.h" 
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerLastRunState.h"
#include "PlayerJumpingShortState.h"
#include "Mario.h"
PlayerWalkingState::PlayerWalkingState()
{
	player->Allow[RUNNING] = true;
	player->Allow[JUMPING_LONG] = true; // can jump in walking state
	player->Allow[JUMPING_SHORT] = true;
	player->Allow[FIRING_FIRE] = false;
	player->Allow[WHIPPING] = false;
	player->Allow[SITTING] = true;
	switch (player->level)
	{
	case SMALL:
		player->Allow[SITTING] = false;
		break;
	case BIG:
		break;
	case RACCOON:
		player->Allow[WHIPPING] = true;
		break;
	case FIRE:
		player->Allow[FIRING_FIRE] = true;
		break;
	}

	//flag
	player->isWhipping = false;
	player->isSitting = false;
	player->isJumping = false;
	player->canFly = false;
	// set bouding box
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;

	//set state by nx and vx
		if (player->nx > 0)
		{
			player->vx = player->vx > player->SpeedX ? player->SpeedX : player->vx + MARIO_INERTIA_WALKING; // vx increase by inertia; max vx = speedPush
		}
		else
		{
			//DebugOut(L"vx-left: %f\n", player->vx);
			player->vx = player->vx < -player->SpeedX ? -player->SpeedX : player->vx - MARIO_INERTIA_WALKING; // vx decrease by inertia; max vx = speedPush
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
			if (abs(player->vx) <= MARIO_WALKING_SPEED)
			{
				if (player->nx > 0)
				{
					stateName = WALKING_RIGHT;
				}
				else stateName = WALKING_LEFT;
			}
			else if (abs(player->vx) > MARIO_WALKING_SPEED && abs(player->vx) <= MARIO_RUNNING_SPEED)
			{
				if (player->nx > 0)
				{
					stateName = WALKING_FAST_RIGHT;
				}
				else
					stateName = WALKING_FAST_LEFT;
			}
			else
			{
				if (player->nx > 0)
				{
					stateName = RUNNING_RIGHT;
					player->canFly = true;
				}
				else
				{
					player->canFly = true;
					stateName = RUNNING_LEFT;
				}
			}
		}

		
	
}


void PlayerWalkingState::HandleKeyBoard()
{
	if (keyCode[DIK_A] &&(keyCode[DIK_LEFT] || keyCode[DIK_RIGHT]))
	{
		player->SpeedX = MARIO_RUNNING_SPEED;
		player->ChangeAnimation(new PlayerWalkingState());
	}
	else if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT] )
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		if (!player->isWalkingComplete)
		{
			player->SpeedX = MARIO_WALKING_SPEED;
			player->nx = -1;
			player->ChangeAnimation(new PlayerWalkingState());
		}
		else player->ChangeAnimation(new PlayerLastRunState());
	}
	else if (keyCode[DIK_RIGHT] )
	{
		if (!player->isWalkingComplete)
		{
			player->SpeedX = MARIO_WALKING_SPEED;
			player->nx = 1;
			player->ChangeAnimation(new PlayerWalkingState());
		}
		else player->ChangeAnimation(new PlayerLastRunState());
	}
	
	
}

void PlayerWalkingState::Update(DWORD dt)
{

	this->HandleKeyBoard();
	if (player->isWaittingPressBtn) // btn left or right is OnUpKey in number of time
	{
		if (player->walkingDirection != player->nx) {
			// if nx != walkingDirection that mean wakling is done and change direction
			player->isWalkingComplete = true;
		}
		else {
			// continue walking in before direction
			player->isWalkingComplete = false;
			player->ChangeAnimation(new PlayerStandingState());
		}
	}
	else
	{
		player->isWalkingComplete = false;
		//DebugOut(L"vx On key Down: %f \n", player->vx);
	}
}

PlayerWalkingState::~PlayerWalkingState()
{

}