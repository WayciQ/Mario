#include "PlayerChangeLevelState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "Mario.h"
#include "Grid.h"
#include "Effects.h"
PlayerChangeLevelState::PlayerChangeLevelState(bool isHurt,TYPE typeChange)
{
	player->Allow[JUMPING] = false;
	player->Allow[WALKING] = false;
	player->vx = 0;
	isChange = false;
	upsize = false;
	if (isHurt) {
		auto e = Effects::CreateEffect(EFFECT_BIGBANG);
		player->startTimeChangeState();
		player->startTimeFreeze();
		switch (player->level)
		{
		case RACCOON:
			grid->AddStaticObject(e, player->x + 10, player->y - 10);
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case FIRE:
			grid->AddStaticObject(e, player->x + 10, player->y - 10);
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case BIG:
			grid->AddStaticObject(e, player->x + 10, player->y - 10);
			isChange = true;
			upsize = false;
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
			player->SetLevel(SMALL);
			break;
		case SMALL:
			stateName = DIE;
			player->isDead = true;
			break;
		}
	}
	else {
		player->isDead = false;
		player->startTimeChangeState();
		if (player->level == SMALL) {
			isChange = true;
			upsize = true;
			player->y -= 36;
			stateName = player->nx > 0 ? UP_SIZE_RIGHT : UP_SIZE_LEFT;
			player->SetLevel(BIG);
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
	if (GetTickCount() - player->untouchableTime >= 200 && !player->isDead )
	{
		if (isChange) {
			if (upsize) {
				player->y -= 36;
				player->SetLevel(BIG);
			}
			else {
				player->SetLevel(SMALL);
			}
			isChange = false;
		}
		player->ChangeState(new PlayerStandingState());
	}
	if (GetTickCount() - player->FreezeTime > 1000)
	{
		player->freeze = false;
		if (GetTickCount() - player->FreezeTime < 1200 && player->isDead) {
			player->vy = -MARIO_JUMP_SPEED_Y;
		}
		if (GetTickCount() - player->FreezeTime < 1400 && player->isDead) {
			player->infor->LifeEarn(-1);
			player->infor->SetSceneId(0);
			player->IsChangeScene = true;
		}
	}
}