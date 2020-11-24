#include "PlayerSittingState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"

PlayerSittingState::PlayerSittingState()
{
	player->Allow[JUMPING_LONG] = true;
	player->Allow[WALKING] = false;
	player->Allow[WHIPPING] = false;
	player->Allow[JUMPING_SHORT] = true;
	player->isSitting = true;
	player->vx = 0;
	player->stateBoundingBox = MARIO_STATE_BIG_SIT_BOUNDING_BOX;
	if (player->nx > 0) {
		stateName = SITTING_RIGHT;
	}
	else stateName = SITTING_LEFT;
}

void PlayerSittingState::Update(DWORD dt)
{
	
	this->HandleKeyBoard();
}
void PlayerSittingState::HandleKeyBoard()
{
	if (keyCode[DIK_DOWN])
	{
	
			if (keyCode[DIK_LEFT])
			{
				
				player->nx = -1;
				player->ChangeAnimation(new PlayerWalkingState());
			}
			else if (keyCode[DIK_RIGHT])
			{
				
				player->nx = 1;
				player->ChangeAnimation(new PlayerWalkingState());
			}
		
	}
	else
	{

		player->ChangeAnimation(new PlayerStandingState());
	}
	
		
	
}
	
PlayerSittingState::~PlayerSittingState() {

}