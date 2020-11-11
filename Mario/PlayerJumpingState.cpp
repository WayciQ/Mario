#include "PlayerJumpingState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerWhippingState.h"
#include "PlayerJumpingShortState.h"
#define MARIO_TIME_FLY 2000
#define MARIO_JUMP_TIME 310

PlayerJumpingState::PlayerJumpingState()
{
	player->Allow[WHIPPING] = false;
	player->Allow[JUMPING_SHORT] = false;
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
	
	player->isJumping = true;

	if (player->canFly)
	{
		if (player->isFlying)
		{
			if (player->nx > 0)
				stateName = FLYING_PUSH_RIGHT;
			else
				stateName = FLYING_PUSH_LEFT;
		}
		else
		{
			if (player->nx > 0)
				stateName = FLYING_RIGHT;
			else
				stateName = FLYING_LEFT;
		}
	}
	else
	{
		if (player->isHolding)
		{
			if (player->nx > 0)
			{
				stateName = STANDING_PICK_RIGHT;
			}
			else stateName = STANDING_PICK_LEFT;
		}
		else {
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
	if (keyCode[DIK_S])
	{
		if (GetTickCount() - player->startJumping > MARIO_JUMP_TIME)
		{
			player->isJumpDone = true;
			player->Allow[JUMPING_LONG] = false;
		}
		else
		{
			player->vy = -MARIO_JUMP_SPEED_Y;

		}
		if (keyCode[DIK_RIGHT]) {
			player->nx = 1;
			if (player->vx < MARIO_WALKING_SPEED) {
				player->vx = MARIO_WALKING_SPEED / 2;
			}
			player->ChangeAnimation(new PlayerJumpingState());
		}
		else if (keyCode[DIK_LEFT])
		{
			player->nx = -1;
			if (player->vx > -MARIO_WALKING_SPEED) {
				player->vx = -MARIO_WALKING_SPEED / 2;
			}
			player->ChangeAnimation(new PlayerJumpingState());
		}
	}
	else if (keyCode[DIK_X]  && player->Allow[FLYING_PUSH])
	{
		if (GetTickCount() - player->startJumping < MARIO_TIME_FLY)
		{
			player->vy = -MARIO_JUMP_SPEED_Y;
			player->vx > -MARIO_WALKING_SPEED;
			 player->isFlying = true;
			
		}
		else {
			
			player->isFlying = false;
			player->vy = 0;
		} 
		
	}
}

void PlayerJumpingState::Update()
{
	this->HandleKeyBoard();
	
	if (player->vy >= 0 || player->isJumpDone)
	{
		player->curY = player->y;
		player->ChangeAnimation(new PlayerFallingState());
	}
	
}

PlayerJumpingState::~PlayerJumpingState()
{
}