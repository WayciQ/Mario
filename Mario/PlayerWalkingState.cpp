#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSittingState.h" 
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerLastRunState.h"
#include "Mario.h"
PlayerWalkingState::PlayerWalkingState()
{
	PrevState = player->state->stateName;
	player->allow[JUMPING] = true;
	player->isWhipping = false;
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	//player->ny = 1;
		if (player->nx > 0)
		{
			if (PrevState == WALKING_RIGHT)
			{
				player->vx = player->vx < player->speedPush ? player->vx + MARIO_INERTIA : player->speedPush;
			}
			stateName = WALKING_RIGHT;
		}
		else
		{
			if (PrevState == WALKING_LEFT)
			{
				player->vx = player->vx > -player->speedPush ? player->vx - MARIO_INERTIA : -player->speedPush;
			}
			stateName = WALKING_LEFT;
		}
	
	
	

}

void PlayerWalkingState::Update()
{
	if (player->isWaittingPress) 
	{
		if (player->walkingDirection != player->nx) {
			player->isWalkingComplete = true;
			DebugOut(L"\n11111");
		}
		else {
			player->isWalkingComplete = false;
		}
	}
	else
	{
		player->isWalkingComplete = false;
		
	}
	this->HandleKeyBoard();

}

void PlayerWalkingState::HandleKeyBoard()
{
	if (keyCode[DIK_A]) {
		player->speedPush = MARIO_WALKING_SPEED_PUSH;
	}
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT])
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		if (!player->isWalkingComplete)
		{
			player->nx = -1;
			player->ChangeAnimation(new PlayerWalkingState());
		}
		else player->ChangeAnimation(new PlayerLastRunState());
		
	}
	else if (keyCode[DIK_RIGHT] )
	{
		if (!player->isWalkingComplete)
		{
			player->nx = 1;
			player->ChangeAnimation(new PlayerWalkingState());
		}
		else player->ChangeAnimation(new PlayerLastRunState());

		
	}
	else 
	{
		if(!player->isWalkingComplete && player->CurAnimation->isLastFrame)
			player->ChangeAnimation(new PlayerStandingState());
	}
}


PlayerWalkingState::~PlayerWalkingState()
{

}