#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "PlayerSittingState.h" 
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "Mario.h"
PlayerWalkingState::PlayerWalkingState(DWORD timeFinish)
{
	timeWalk = GetTickCount();
	this->timeFinish = timeFinish;
	player->allow[JUMPING] = true;
	player->allow[WHIPPING] = true;
	player->isWhipping = false;
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	//player->ny = 1;
	if (player->nx > 0)
	{
		stateName = WALKING_RIGHT;
		player->vx = MARIO_WALKING_SPEED;
	}
	else
	{
		stateName = WALKING_LEFT;
		player->vx = -MARIO_WALKING_SPEED;
	}
	

}

void PlayerWalkingState::walking(DWORD dt)
{

	if (player->x < dt)
	{
		if (player->x >= dt - 2)
		{
			//get in the position
			player->IsWalkingComplete = true;
			player->ChangeAnimation(new PlayerStandingState());
			return;
		}
		player->nx = 1;
	}
	else
	{
		if (player->x <= dt + 2)
		{
			//get in the position
			player->IsWalkingComplete = true;
				player->ChangeAnimation(new PlayerStandingState());
			return;
		}
		player->nx = -1;
	}
	player->ChangeAnimation(new PlayerWalkingState(dt));
}

void PlayerWalkingState::Update()
{

	if (timeFinish != 0)
		walking(timeFinish);
	else
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
		player->nx = -1;
		player->ChangeAnimation(new PlayerWalkingState());
	}
	else if (keyCode[DIK_RIGHT])
	{
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