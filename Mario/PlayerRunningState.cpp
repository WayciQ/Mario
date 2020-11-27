#include "PlayerRunningState.h"
#include "PlayerWalkingState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerFlyingState.h"
#include "Mario.h"
PlayerRunningState::PlayerRunningState() {
	player->Allow[JUMPING] = false;
	player->Allow[JUMPING_SHORT] = false;
	player->Allow[FLYING_PUSH] = false;

	DebugOut(L"[info] RUNNING: vx: %f\n", player->vx);

	if (abs(player->vx) >= MARIO_RUNNING_SPEED)
	{
		if (player->nx > 0)
		{
			stateName = RUNNING_RIGHT;
		}
		else stateName = RUNNING_LEFT;
		if (player->level == RACCOON)
			player->Allow[FLYING] = true;
		else player->Allow[JUMPING] = true;
	}
	else 
	{
		if (player->nx > 0)
		{
			stateName = WALKING_FAST_RIGHT;
		}
		else stateName = WALKING_FAST_LEFT;
	}
	

	if (player->level == RACCOON)
	{
		player->Allow[FLYING_PUSH] = true;
	}
	if (player->nx > 0)
		player->vx = player->vx > MARIO_RUNNING_SPEED ? MARIO_RUNNING_SPEED : player->vx + MARIO_INERTIA_WALKING;
	else
		player->vx = player->vx < -MARIO_RUNNING_SPEED ? -MARIO_RUNNING_SPEED : player->vx - MARIO_INERTIA_WALKING;
	
}

void PlayerRunningState::HandleKeyBoard() {

	if (keyCode[DIK_A])
	{
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
	else
	{
		player->ChangeAnimation(new PlayerWalkingState());
	}
}

void PlayerRunningState::Update(DWORD dt)
{
	this->HandleKeyBoard();
}
PlayerRunningState::~PlayerRunningState(){}
