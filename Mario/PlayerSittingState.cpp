#include "PlayerSittingState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "Mario.h"

PlayerSittingState::PlayerSittingState()
{
	player->allow[JUMPING] = false;
	player->allow[WHIPPING] = false;
	player->vx = 0;
	player->vy = 0;
	
	player->stateBoundingBox = MARIO_STATE_BIG_SIT_BOUNDING_BOX;
	if (player->nx > 0) {
		stateName = SITTING_RIGHT;
	}
	else stateName = SITTING_LEFT;
}

void PlayerSittingState::Update()
{
	this->HandleKeyBoard();
}
void PlayerSittingState::HandleKeyBoard()
{
	if (!keyCode[DIK_DOWN])
	{
		player->allow[JUMPING] = true;
		player->y -= 11;
		
		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			player->ChangeAnimation(new PlayerWalkingState());
		}
		else
		{
			player->ChangeAnimation(new PlayerStandingState());
		}
	}
}
PlayerSittingState::~PlayerSittingState() {

}