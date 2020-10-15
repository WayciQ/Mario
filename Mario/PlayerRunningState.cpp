#include "PlayerRunningState.h"
#include "PlayerWalkingState.h"
#include "PlayerStandingState.h"
#include "Mario.h"
PlayerRunningState::PlayerRunningState() {
	player->allow[JUMPING] = true;
	player->allow[SITTING] = true;
	player->isRunning = true;
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
	if (player->vx >= MARIO_RUNNING_SPEED) 
	{
			stateName = RUNNING_RIGHT;
	}
	else if (player->vx <= -MARIO_RUNNING_SPEED)
	{
		stateName = RUNNING_LEFT;
	}
	player->speedJump = player->vx;


}
PlayerRunningState::~PlayerRunningState(){}
void PlayerRunningState::Update()
{
	if (!player->isRunning)
	{
		player->ChangeAnimation(new PlayerWalkingState());
		return;
	}
	this->HandleKeyBoard();
}
void PlayerRunningState::HandleKeyBoard(){
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