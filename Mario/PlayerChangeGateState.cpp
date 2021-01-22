#include "PlayerChangeGateState.h"
#include "PlayerStandingState.h"
#include "Mario.h"
#define Y_MOVE_UP	 posY - 48
#define Y_MOVE_DOWN	 posY + 48
PlayerChangeGateState::PlayerChangeGateState(int way,bool isOut,float x, float y)
{
	waymove = way;
	startY = player->y;
	posX = x;
	posY = y;
	isChangeDone = isOut;
	player->gravity = 0;
	player->Allow[WALKING] = false;
	player->Allow[JUMPING] = false;
	player->Allow[SITTING] = false;
	player->Allow[FALLING] = false;
	stateName = IDLE_CHANGE_GATE;
	switch (waymove)
	{
	case -2:
		if (!isOut)
			player->y -= MARIO_JUMP_SPEED_Y;
		
		break;
	case 2:
		if (!isOut)
			player->y += MARIO_JUMP_SPEED_Y;
		break;
	default:
		break;
	}
}

void PlayerChangeGateState::Update(DWORD dt)
{
	if (waymove == -2)
	{

		if (player->y < Y_MOVE_UP) {
			if (isChangeDone) {
				player->nx = 1;
				player->ChangeState(new PlayerStandingState());
				player->SetPosition(posX, posY);
			}
			else {
				player->IsChangeTrigger = true;
			}
		}
	}
	else if(waymove == 2) {
		if (player->y > Y_MOVE_DOWN) {
			if (isChangeDone) {
				player->nx = 1;
				player->ChangeState(new PlayerStandingState());
				player->SetPosition(posX, posY);
			}
			else {
				player->IsChangeTrigger = true;
			}
		}
	}
}

void PlayerChangeGateState::HandleKeyBoard()
{
}
