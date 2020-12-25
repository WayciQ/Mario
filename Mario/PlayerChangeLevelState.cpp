#include "PlayerChangeLevelState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "Mario.h"
#include "Grid.h"
#include "EffectBigBang.h"
PlayerChangeLevelState::PlayerChangeLevelState(bool isHurt,TYPE typeChange)
{
	
	player->vx = 0;
	isChange = false;
	if (isHurt) {
		player->startTimeChangeState();
		player->startTimeFreeze();
		switch (player->level)
		{
		case RACCOON:
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case FIRE:
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case BIG:
			isChange = true;
			upsize = false;
			player->vy = 0;
			player->gravity = 0;
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
			break;
		case SMALL:
			stateName = DIE;
			player->isDead = true;
			break;
		}
	}
	else {
		
		if (player->level == SMALL) {
			player->startTimeChangeState();
			player->isDead = false;
			isChange = true;
			upsize = true;
			player->y -= 12;
			player->vy = 0;
			player->gravity = 0;
			player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
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
	if (!player->isDead || !player->untouchable) {
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
}

void PlayerChangeLevelState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	if (!player->untouchable && !player->isDead )
	{
		if (isChange) {
			if (upsize) {
				player->SetLevel(BIG);
			}
			else {
				player->SetLevel(SMALL);
			}
			isChange = false;
		}
		else
		player->ChangeState(new PlayerStandingState());
	}
	if (GetTickCount() - player->FreezeTime > 1000)
	{
		player->freeze = false;
		if (GetTickCount() - player->FreezeTime < 1200 && player->isDead) {
			player->vy = -MARIO_JUMP_SPEED_Y;
		}
		if (GetTickCount() - player->FreezeTime > 1400 && player->isDead) {
			player->infor->LifeEarn(-1);
			player->infor->SetSceneId(0);
			player->IsChangeScene = true;
		}
		
	}
		
	
	
	
}