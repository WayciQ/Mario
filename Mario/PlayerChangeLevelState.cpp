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
		player->startTimeFreeze();
		switch (player->level)
		{
		case RACCOON:
			player->startTimeDead();
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case BIG:
			player->startTimeDead();
			isChange = true;
			upsize = false;
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
			break;
		case FIRE:
			player->startTimeDead();
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case SMALL:
			player->Allow[WALKING] = false;
			player->Allow[JUMPING] = false;
			stateName = DIE;
			player->isDead = true;
			player->vy = -MARIO_JUMP_SPEED_Y;
		}
	}
	else {
		player->startTimeDead();
		if (player->level == SMALL) {
			isChange = true;
			upsize = true;
			player->SetLevel(BIG);
			player->y -= 20;
			stateName = player->nx > 0 ? UP_SIZE_RIGHT : UP_SIZE_LEFT;
		}
		else {
			player->SetLevel(typeChange);
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
				player->SetLevel(SMALL);
			}
			isChange = false;
		}
		player->ChangeState(new PlayerStandingState());
		
	}
	if (GetTickCount() - player->FreezeTime > 500)
	{
		player->freeze = false;
	}
	if (player->isDead && player->vy > 0) {
		player->infor->LifeEarn(-1);
		player->scene_id = 0;
		game->SwitchScene(player->scene_id);
	}
}