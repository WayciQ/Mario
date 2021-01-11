#include "PlayerFlyingState.h"
#include "PlayerFallingState.h"
#include "Mario.h"
#define MARIO_FLY_TIME	5000
#define MARIO_FLY_SPEED 0.75
PlayerFlyingState::PlayerFlyingState() {
	player->Allow[JUMPING] = false;
	player->isOnSky = true;
	player->isFlying = true;
	player->vy = -MARIO_FLY_SPEED;

	if (player->nx > 0)
	{
		stateName = FLYING_RIGHT;
	}
	else stateName = FLYING_LEFT;
	
}

void PlayerFlyingState::HandleKeyBoard() 
{
	if (keyCode[DIK_S])
	{
		/*player->ChangeState(new PlayerFlyingState());*/
	}
	else if (keyCode[DIK_X])
	{
		if (GetTickCount() - player->startJumping > 5000)
		{
			player->isJumpDone = true;
			player->isFlying = false;
		}
		else player->vy = -MARIO_JUMP_SPEED_Y;
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->vx = -MARIO_WALKING_SPEED;
	}
	else if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->vx = MARIO_WALKING_SPEED;
	}
}

void PlayerFlyingState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	if (player->vy >= 0) {
		player->ChangeState(new PlayerFallingState());
	}

	if (GetTickCount() - player->startTimeFly > MARIO_FLY_TIME)
	{
		player->Allow[FLYING] = false;
		player->isFlying = false;
	}

}