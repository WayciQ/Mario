#include "PlayerStandingState.h"
#include "PlayerState.h"
#include "Mario.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "PlayerWhippingState.h"
#include "PlayerJumpingShortState.h"
PlayerStandingState::PlayerStandingState() {
	
	// allow state by level
	player->Allow[JUMPING_LONG] = true; // allow jump in standing state
	player->Allow[WALKING] = true; // allow walk
	player->Allow[JUMPING_SHORT] = true;
	player->Allow[FLYING_PUSH] = false;
	player->Allow[WHIPPING] = false;
	player->Allow[SITTING] = true;
	player->Allow[FIRING_FIRE] = false;

	switch (player->level)
	{
	case SMALL:
		player->Allow[SITTING] = false;
		break;
	case BIG:
		break;
	case RACCOON:
		player->Allow[WHIPPING] = true;
		break;
	case FIRE:
		player->Allow[FIRING_FIRE] = true;
		break;
	}
	
	// set bounding box in standing state
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;

	// flag state s
	player->isWhipping = false;
	player->isSitting = false;
	player->isJumping = false;
	player->isShooting = false;
	// set state by nx
	if (player->isHolding)
	{
		if (player->nx > 0)
		{
			stateName = STANDING_PICK_RIGHT;
		}
		else stateName = STANDING_PICK_LEFT;
	}
	else
	{
		if (player->nx > 0)
			stateName = STANDING_RIGHT;
		else stateName = STANDING_LEFT;
	}

}

void PlayerStandingState::HandleKeyBoard() {
	
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT])
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		player->ChangeAnimation(new PlayerWalkingState());
	}
	else if (keyCode[DIK_DOWN] && player->Allow[SITTING]) // small level dosen't have state sit
	{
		player->ChangeAnimation(new PlayerSittingState());
	}
	else if (keyCode[DIK_X])
	{
		player->ChangeAnimation(new PlayerJumpingShortState()); 
	}
	
}

void PlayerStandingState::Update()
{
	this->HandleKeyBoard(); // loop

	if (player->vx < MARIO_INERTIA_WALKING && player->vx > -MARIO_INERTIA_WALKING)
	{
		player->vx = 0;
	}
	else
	{
		if (player->vx > 0)
		{
			player->vx = player->vx < 0 ? 0 : player->vx - MARIO_INERTIA_WALKING;
		}
		else
		{
			player->vx = player->vx > 0 ? 0 : player->vx + MARIO_INERTIA_WALKING;
			
		}
	}
		

	
	
}

PlayerStandingState::~PlayerStandingState()
{
}

