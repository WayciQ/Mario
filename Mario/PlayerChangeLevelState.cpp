#include "PlayerChangeLevelState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "Mario.h"
#include "Grid.h"
#include "EffectBigBang.h"
PlayerChangeLevelState::PlayerChangeLevelState(bool isdead,TYPE typeChange)
{
	player->vx = 0;
	
	//auto effect = new EffectBigBang();
	isChange = false;
	if (isdead) {
		
		player->freeze = true;
		player->startTimeDead();
		player->startTimeFreeze();
		switch (player->level)
		{
		case RACCOON:
			player->level = BIG;
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case BIG:
			isChange = true;
			upsize = false;
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
			break;
		case FIRE:
			player->level = BIG;
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case SMALL:
			stateName = DIE;
			player->isDead = true;
			player->vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else {
		player->startTimeDead();
		if (player->level == SMALL) {
			isChange = true;
			upsize = true;
			player->level = BIG;
			player->y -= 20;
			stateName = player->nx > 0 ? UP_SIZE_RIGHT : UP_SIZE_LEFT;
		}
		else {
			player->level = typeChange;
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
		}
	}

}

void PlayerChangeLevelState::HandleKeyBoard() {
	if (keyCode[DIK_LEFT] && keyCode[DIK_RIGHT])
	{
		player->ChangeState(new PlayerStandingState());
	}
	else if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		player->ChangeState(new PlayerWalkingState());
	}
	else if (keyCode[DIK_DOWN] && player->Allow[SITTING]) // small level dosen't have state sit
	{
		player->ChangeState(new PlayerSittingState());
	}
}

void PlayerChangeLevelState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	if (GetTickCount() - player->untouchableTime > MARIO_UNTOUCHABLE_TIME && !player->isDead )
	{
		if (isChange) {
			if (upsize) {
				player->ChangeState(new PlayerChangeLevelState(false, BIG));
			}
			else {
				player->level = SMALL;
			}
			isChange = false;
		}
		player->ChangeState(new PlayerStandingState());
		
	}
	if (GetTickCount() - player->FreezeTime > 500)
	{
		player->freeze = false;
	}
}