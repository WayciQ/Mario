#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSittingState.h" 
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerLastRunState.h"
#include "PlayerRunningState.h"
#include "Mario.h"
PlayerWalkingState::PlayerWalkingState()
{
	player->Allow[RUNNING] = true;
	player->Allow[JUMPING] = true; // can jump in walking state
	switch (player->level)
	{
	case SMALL:
		player->Allow[WHIPPING] = false;
		player->Allow[SITTING] = false;
		break;
	case BIG:
		player->Allow[WHIPPING] = false;
		player->Allow[SITTING] = true;
		break;
	case RACCOON:
		player->Allow[WHIPPING] = true;
		player->Allow[SITTING] = true;
		break;
	case FIRE:
		break;
	}

	//flag
	player->isWhipping = false;
	player->isRunning = false;
	player->isSitting = false;
	// set bouding box
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;

	//set state by nx and vx
		if (player->nx > 0)
		{
			player->vx = player->vx > MARIO_WALKING_SPEED ? MARIO_WALKING_SPEED : player->vx + MARIO_INERTIA_WALKING; // vx increase by inertia; max vx = speedPush
			stateName = WALKING_RIGHT;
		}
		else
		{
			//DebugOut(L"vx-left: %f\n", player->vx);
			player->vx = player->vx < -MARIO_WALKING_SPEED ? -MARIO_WALKING_SPEED : player->vx - MARIO_INERTIA_WALKING; // vx decrease by inertia; max vx = speedPush
			stateName = WALKING_LEFT;
		}
		player->speedJump = player->vx;
	
	

}

void PlayerWalkingState::Update()
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
		}
		
	}
	else
	{
		player->isWalkingComplete = false;

		// vx will be minus by inertia cause btn left or right dosen't press
		if (stateName == WALKING_RIGHT)
		{
			player->vx = player->vx < 0 ? 0 : player->vx - 3 * MARIO_INERTIA_WALKING;

			if (player->vx == 0 && player->CurAnimation->isLastFrame) {
				player->ChangeAnimation(new PlayerStandingState());
				return;
			}
		}
		else if (stateName == WALKING_LEFT)
		{
			player->vx = player->vx > 0 ? 0 : player->vx + 3 * MARIO_INERTIA_WALKING;
			if (player->vx == 0 && player->CurAnimation->isLastFrame) {
				player->ChangeAnimation(new PlayerStandingState());
				return;
			}
		}
	}


}

void PlayerWalkingState::HandleKeyBoard()
{
	if (keyCode[DIK_A])
	{
		if (!player->isRunning && player->Allow[RUNNING])
		{	
			player->isRunning = true;
			player->ChangeAnimation(new PlayerRunningState());
			
		}
	}
	else if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT] )
	{
		player->isSitWalk = true;
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_DOWN] && player->Allow[SITTING]) // small level dosen't have state sit
	{
		player->vx = 0;
		player->ChangeAnimation(new PlayerSittingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		if (!player->isWalkingComplete)
		{
			player->nx = -1;
			player->ChangeAnimation(new PlayerWalkingState());
		}
		else player->ChangeAnimation(new PlayerLastRunState());
	}
	else if (keyCode[DIK_RIGHT] )
	{
		if (!player->isWalkingComplete)
		{
			player->nx = 1;
			player->ChangeAnimation(new PlayerWalkingState());
		}
		else player->ChangeAnimation(new PlayerLastRunState());
	}
	
}


PlayerWalkingState::~PlayerWalkingState()
{

}