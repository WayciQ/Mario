#include "PlayerChangeLevelState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "Mario.h"
#include "Grid.h"
#include "Effects.h"
#define BIGBANG 10
#define X_SPAW 36
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
		player->isDead = false;
		switch (player->level)
		{
		case RACCOON:
			grid->AddStaticObject(e, player->x + BIGBANG, player->y - BIGBANG);
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case FIRE:
			grid->AddStaticObject(e, player->x + BIGBANG, player->y - BIGBANG);
			player->SetLevel(BIG);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		case BIG:
			grid->AddStaticObject(e, player->x + BIGBANG, player->y - BIGBANG);
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
			player->y -= X_SPAW;
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
	if (GetTickCount() - player->untouchableTime >= 400 && !player->isDead )
	{
		if (isChange) {
			if (upsize) {
				player->y -= X_SPAW;
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