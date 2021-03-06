#include "PlayerChangeLevelState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "Mario.h"
#include "Grid.h"
#include "Effects.h"
#define BIGBANG 10
#define X_SPAW 36
#define TIME_FREEZE 500
PlayerChangeLevelState::PlayerChangeLevelState(bool isHurt,TYPE typeChange)
{
	player->Allow[JUMPING] = false;
	player->Allow[WALKING] = false;
	player->Allow[FALLING] = false;
	player->vx = 0;
	player->vy = 0;
	isChangeState = false;
	level = typeChange;
	upsize = 0;
	if (isHurt) {
		auto e = Effects::CreateEffect(EFFECT_BIGBANG);
		
		player->startTimeFreeze();
		player->isDead = false;
		switch (player->level)
		{
		case RACCOON:
			grid->AddMovingObject(e, player->x + BIGBANG, player->y - BIGBANG);
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case FIRE:
			grid->AddMovingObject(e, player->x + BIGBANG, player->y - BIGBANG);
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case BIG:
			player->isFreezeTime = false;
			isChangeState = true;
			upsize = 0;
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
			break;
		case SMALL:
			player->startTimeFreeze();
			player->isFreezeTime = false;
			stateName = DIE;
			player->isDead = true;
			break;
		}
	}
	else {
		player->isDead = false;
		if (player->level == SMALL) {
			player->startTimeFreeze();
			player->isFreezeTime = false;
			isChangeState = true;
			upsize = 1;
			player->y -= X_SPAW;
			player->gravity = 0;
			stateName = player->nx > 0 ? UP_SIZE_RIGHT : UP_SIZE_LEFT;
		}
		else {
			isChangeState = false;
			player->startTimeChangeState();
			player->SetLevel(typeChange);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
		}

	}

}

void PlayerChangeLevelState::HandleKeyBoard() {
	if (!player->isDead && !player->isFreezeTime && !isChangeState) {
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
	if (GetTickCount() - player->FreezeTime > TIME_FREEZE && isChangeState)
	{
			if (upsize == 1) {

				player->SetLevel(BIG);
			}
			else if(upsize == 0) {
				player->SetLevel(SMALL);
			}
			else {
				
			}
			isChangeState = false;
			player->ChangeState(new PlayerStandingState());
	}
	if (GetTickCount() - player->FreezeTime > TIME_FREEZE && player->isFreezeTime)
	{
		player->isFreezeTime = false;
		player->ChangeState(new PlayerStandingState());
		player->startTimeChangeState();
	}
	if (GetTickCount() - player->FreezeTime > TIME_FREEZE && player->isDead)
	{
		player->infor->LifeEarn(-1);
		player->infor->SetSceneId(0);
		player->IsChangeScene = true;
	}
}
