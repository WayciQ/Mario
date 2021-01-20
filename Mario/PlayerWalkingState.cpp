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

	player->isWhipping = false;
	player->isSitting = false;
	player->isJumping = false;
	
	// set bouding box
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
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
		if (player->nx > 0)
		{
			stateName = WALKING_RIGHT;
		}
		else stateName = WALKING_LEFT;
	}
	
	if (player->nx > 0)
		player->vx = player->vx > MARIO_WALKING_SPEED ? MARIO_WALKING_SPEED : player->vx + MARIO_INERTIA_WALKING;
	else 
		player->vx = player->vx < -MARIO_WALKING_SPEED ? -MARIO_WALKING_SPEED : player->vx - MARIO_INERTIA_WALKING;

}


void PlayerWalkingState::HandleKeyBoard()
{
	if (keyCode[DIK_A] && (keyCode[DIK_RIGHT] || keyCode[DIK_LEFT]) && !player->isPicking)
	{
		//player->ChangeState(new PlayerRunningState());
		if (!player->isWalkingComplete)
		{
			player->ChangeState(new PlayerRunningState());
		}
		else player->ChangeState(new PlayerLastRunState());
	}
	else if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT] )
	{
		player->ChangeState(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		if (!player->isWalkingComplete)
		{
			player->nx = -1;
			player->ChangeState(new PlayerWalkingState());
		}
		else player->ChangeState(new PlayerLastRunState());
	}
	else if (keyCode[DIK_RIGHT])
	{
		if (!player->isWalkingComplete)
		{
			
			player->nx = 1;
			player->ChangeState(new PlayerWalkingState());
		}
		else player->ChangeState(new PlayerLastRunState());
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
			player->ChangeState(new PlayerStandingState());
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