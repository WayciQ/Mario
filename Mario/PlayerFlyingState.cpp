#include "PlayerFlyingState.h"
#include "PlayerFallingState.h"
#include "Mario.h"
#define MARIO_FLY_TIME	5000
PlayerFlyingState::PlayerFlyingState() {
	//DebugOut(L"[info] FLYING: vx: %f\n", player->vx);

	if (player->isFlying)
	{
		player->vy = -0.2f;
	}
	player->isOnSky = true;
	player->isFlying = true;
	
	if (player->isFlyingPush && player->level == RACCOON)
	{
		if (player->nx > 0)
		{
			stateName = FLYING_PUSH_RIGHT;
		}
		else stateName = FLYING_PUSH_LEFT;
	}
	else
	{
		if (player->nx > 0)
		{
			stateName = FLYING_RIGHT;
		}
		else stateName = FLYING_LEFT;
	}
}

void PlayerFlyingState::HandleKeyBoard() 
{
	if (GetTickCount() - player->startJumping > 4000)
	{
		player->isJumpDone = true;
		player->isFlying = false;
		
	}
	else {
		if (keyCode[DIK_X])
		{
			player->vy = -MARIO_JUMP_SPEED_Y;
		}
	}
	
}

void PlayerFlyingState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	if (player->isJumpDone || player->vy >=0)
	{
		player->curY = player->y;
		player->ChangeAnimation(new PlayerFallingState());
	}
}