#include "PlayerRunningState.h"
#include "PlayerWalkingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"
PlayerRunningState::PlayerRunningState() {
	player->Allow[JUMPING_LONG] = true;
	player->Allow[JUMPING_SHORT] = true;
	player->Allow[FLYING_PUSH] = false;
	player->isJumping = false;
	// inertia
	if (player->nx > 0)
	{
		player->vx = player->vx > MARIO_RUNNING_SPEED ? MARIO_RUNNING_SPEED : player->vx + MARIO_INERTIA_RUNNING; // vx increase by inertia; max vx = speedPush
		
	}
	else
	{
		player->vx = player->vx < -MARIO_RUNNING_SPEED ? -MARIO_RUNNING_SPEED : player->vx - MARIO_INERTIA_RUNNING; // vx decrease by inertia; max vx = speedPush
		
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
		if (player->nx > 0)
		{
			stateName = WALKING_FAST_RIGHT;
		}
		else
		stateName = WALKING_FAST_LEFT;

		if (player->vx >= MARIO_RUNNING_SPEED)
		{
			stateName = RUNNING_RIGHT;
			player->canFly = true;
		}
		else if (player->vx <= -MARIO_RUNNING_SPEED)
		{
			player->canFly = true;
			stateName = RUNNING_LEFT;
		}
	}

	if (player->level == RACCOON)
	{
		player->Allow[FLYING_PUSH] = true;
	}
	// max speed
	

}

void PlayerRunningState::HandleKeyBoard() {
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT])
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		player->nx = -1;
		player->ChangeAnimation(new PlayerRunningState());

	}
	else if (keyCode[DIK_RIGHT])
	{
		player->nx = 1;
		player->ChangeAnimation(new PlayerRunningState());
	}else if (keyCode[DIK_X])
	{
		player->isFlying = true;
		if ((keyCode[DIK_RIGHT]))
		{
			player->nx = 1;
			player->ChangeAnimation(new PlayerJumpingState());
		}
		else if ((keyCode[DIK_LEFT]))
		{
			player->nx = -1;
			player->ChangeAnimation(new PlayerJumpingState());
		}
		else
		{
			player->ChangeAnimation(new PlayerJumpingState());
		}
	}
	
}

void PlayerRunningState::Update()
{
	this->HandleKeyBoard();
	if (!player->isRunning)
	{
		player->ChangeAnimation(new PlayerStandingState());
	}

}
PlayerRunningState::~PlayerRunningState(){}
