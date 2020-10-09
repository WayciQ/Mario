#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSittingState.h" 
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerLastRunState.h"
#include "Mario.h"
PlayerWalkingState::PlayerWalkingState(DWORD timeFinish)
{
	PrevState = player->state->stateName;
	
	timeWalk = GetTickCount();
	this->timeFinish = timeFinish;
	player->allow[JUMPING] = true;
	player->allow[WHIPPING] = true;
	player->isWhipping = false;
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	//player->ny = 1;
	if (player->nx > 0)
	{
		if (PrevState == WALKING_RIGHT)
		{
			player->vx = player->vx  < player->speedPush ? player->vx + MARIO_INERTIA : player->speedPush;
			DebugOut(L"speed: %f \n", player->vx);
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

void PlayerWalkingState::walking(DWORD dt)
{
	if (player->x < dt)
	{
		if (player->x >= dt - 10)
		{
			//get in the position
			player->isWalkingComplete = true;
			player->ChangeAnimation(new PlayerStandingState());
			return;
		}
		player->nx = 1;
	}
	else
	{
		if (player->x <= dt + 10)
		{
			//get in the position
			player->isWalkingComplete = true;
				player->ChangeAnimation(new PlayerStandingState());
			return;
		}
		player->nx = -1;
	}
	player->ChangeAnimation(new PlayerWalkingState(dt));
}

void PlayerWalkingState::Update()
{

	/*if (player->isWalkingComplete)
		player->ChangeAnimation(new PlayerLastRunState());
	else*/
		this->HandleKeyBoard();

}

void PlayerWalkingState::HandleKeyBoard()
{

	if (keyCode[DIK_DOWN])
	{
		player->ChangeAnimation(new PlayerSittingState());
	}
	else if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT])
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT])
	{
		if (keyCode[DIK_A]) {
			player->speedPush = MARIO_WALKING_SPEED_PUSH;
		}
		player->nx = -1;
		player->ChangeAnimation(new PlayerWalkingState());
	}
	else if (keyCode[DIK_RIGHT])
	{
		if (keyCode[DIK_A]) {
			player->speedPush = MARIO_WALKING_SPEED_PUSH;
		}
		player->nx = 1;
		player->ChangeAnimation(new PlayerWalkingState());
	}
	else if(keyCode[DIK_S]) {
		player->ChangeAnimation(new PlayerWhippingState());
	}
	else 
	{
		player->ChangeAnimation(new PlayerStandingState);
	}
}


PlayerWalkingState::~PlayerWalkingState()
{

}