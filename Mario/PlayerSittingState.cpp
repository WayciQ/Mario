#include "PlayerSittingState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "Mario.h"

PlayerSittingState::PlayerSittingState()
{
	player->Allow[JUMPING] = true;
	player->Allow[WALKING] = false;
	player->Allow[WHIPPING] = false;
	player->Allow[JUMPING_SHORT] = true;
	//DebugOut(L"[info] SITTING: vx: %f\n", player->vx);
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
				player->ChangeState(new PlayerWalkingState());
			}
			else if (keyCode[DIK_RIGHT])
			{
				
				player->nx = 1;
				player->ChangeState(new PlayerWalkingState());
			}
		
	}
	else
	{

		player->ChangeState(new PlayerStandingState());
	}
	
		
	
}
	
PlayerSittingState::~PlayerSittingState() {

}