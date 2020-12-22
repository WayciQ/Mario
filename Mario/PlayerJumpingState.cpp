#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerWhippingState.h"
#define MARIO_TIME_FLY 2000
#define MARIO_JUMP_TIME 310

PlayerJumpingState::PlayerJumpingState()
{

	player->Allow[WHIPPING] = false; 
	player->Allow[FIRING_FIRE] = false;
	//DebugOut(L"[info] JUMPING: vx: %f\n", player->vx);
	switch (player->level)
	{
	case BIG:
		break;
	case RACCOON:
		player->Allow[WHIPPING] = true;
		break;
	case FIRE:
		player->Allow[FIRING_FIRE] = true;
		break;
	}

	if (!player->isJumping)
	{
		
	}
	player->isOnSky = true;
	player->isJumping = true;

	if (!player->isJumpingShort && player->Allow[JUMPING_SHORT])
	{
		//player->vy = -MARIO_JUMP_SPEED_Y;
		//player->gravity = 0.0001;
		player->isJumpingShort = true;
		if (player->nx > 0) {
			stateName = JUMPING_RIGHT;
		}
		else {
			stateName = JUMPING_LEFT;
		}
	}

	
	
	if (player->isPicking)
	{
		if (player->nx > 0)
		{
			stateName = STANDING_PICK_RIGHT;
		}
		else stateName = STANDING_PICK_LEFT;
	}
	else {

		if (player->isFlying)
		{
			if (player->nx > 0)
			{
				stateName = FLYING_RIGHT;
			}
			else stateName = FLYING_LEFT;
		}
		else
		{
			if (player->nx > 0)
			{
				stateName = JUMPING_RIGHT;
			}
			else
			{
				stateName = JUMPING_LEFT;
			}
		}
	}

	if (player->isSitting)
	{
		if (player->nx > 0)
			stateName = SITTING_RIGHT;
		else
			stateName = SITTING_LEFT;
	}
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
}
void PlayerJumpingState::HandleKeyBoard()
{
	if (keyCode[DIK_S] && player->Allow[JUMPING])
	{
		if (GetTickCount() - player->startJumping > MARIO_JUMP_TIME)
		{
			player->isJumpDone = true;
			player->Allow[JUMPING] = false;
		}
		else
		{
			player->vy = -MARIO_JUMP_SPEED_Y;
		}
	}
	else if (keyCode[DIK_RIGHT])
	{
		player->vx = MARIO_WALKING_SPEED;
		player->nx = 1;
		player->ChangeState(new PlayerJumpingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		player->vx = -MARIO_WALKING_SPEED;
		player->nx = -1;
		player->ChangeState(new PlayerJumpingState());
	}
}

void PlayerJumpingState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	
	if (player->vy >= 0 || player->isJumpDone)
	{
		player->curY = player->y;
		player->ChangeState(new PlayerFallingState());
	}
}

PlayerJumpingState::~PlayerJumpingState()
{
}