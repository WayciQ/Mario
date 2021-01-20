 #include "PlayerRunningState.h"
#include "PlayerWalkingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerFlyingState.h"
#include "PlayerLastRunState.h"
#include "Mario.h"
PlayerRunningState::PlayerRunningState() {
	player->Allow[JUMPING] = false;
	player->Allow[PICKING] = false;
	if (player->level == RACCOON) {
		player->Allow[JUMPING] = false;
		player->Allow[FLYING] = true;
	}
	else {
		player->Allow[JUMPING] = true;
		player->Allow[FLYING] = false;
	}
	if (abs(player->vx) >= MARIO_RUNNING_SPEED)
	{
		if (player->nx > 0)
		{
			stateName = RUNNING_RIGHT;
		}
		else stateName = RUNNING_LEFT;
	}
	else 
	{
		if (player->nx > 0)
		{
			stateName = WALKING_FAST_RIGHT;
		}
		else stateName = WALKING_FAST_LEFT;
		
	}
	if (player->nx > 0)
		player->vx = player->vx > MARIO_RUNNING_SPEED ? MARIO_RUNNING_SPEED : player->vx + MARIO_INERTIA_WALKING;
	else
		player->vx = player->vx < -MARIO_RUNNING_SPEED ? -MARIO_RUNNING_SPEED : player->vx - MARIO_INERTIA_WALKING;
	
	
}

void PlayerRunningState::HandleKeyBoard() {

	if (keyCode[DIK_A])
	{
		player->isRunning = true;
		if (keyCode[DIK_LEFT])
		{
			if (!player->isWalkingComplete)
			{
				player->nx = -1;
				player->ChangeState(new PlayerRunningState());
			}
			else {
				player->ChangeState(new PlayerLastRunState());
			}
		}
		else if (keyCode[DIK_RIGHT])
		{
			if (!player->isWalkingComplete)
			{

				player->nx = 1;
				player->ChangeState(new PlayerRunningState());
			}
			else {
				player->ChangeState(new PlayerLastRunState());
			}
		}
	}/*
	else {
		player->isRunning = false;
		if (player->nx > 0)
		{
			player->vx = player->vx <= 0 ? 0 : player->vx - MARIO_INERTIA_WALKING;
		}
		else
		{
			player->vx = player->vx >= 0 ? 0 : player->vx + MARIO_INERTIA_WALKING;

		}
		player->ChangeState(new PlayerRunningState());
	}*/
}

void PlayerRunningState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	/*if (abs(player->vx) <= MARIO_WALKING_SPEED)
	{
		player->ChangeState(new PlayerStandingState());
	}*/
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
PlayerRunningState::~PlayerRunningState(){}
