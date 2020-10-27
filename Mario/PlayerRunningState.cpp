#include "PlayerRunningState.h"
#include "PlayerWalkingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"
PlayerRunningState::PlayerRunningState() {
	player->Allow[JUMPING_LONG] = true;
	player->Allow[JUMPING_SHORT] = true;
	player->isJumping = false;
	// inertia
	if (player->nx > 0)
	{
		player->vx = player->vx > MARIO_RUNNING_SPEED ? MARIO_RUNNING_SPEED : player->vx + MARIO_INERTIA_RUNNING; // vx increase by inertia; max vx = speedPush
		stateName = WALKING_FAST_RIGHT;
	}
	else
	{
		player->vx = player->vx < -MARIO_RUNNING_SPEED ? -MARIO_RUNNING_SPEED : player->vx - MARIO_INERTIA_RUNNING; // vx decrease by inertia; max vx = speedPush
		stateName = WALKING_FAST_LEFT;
	}

	// max speed
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
