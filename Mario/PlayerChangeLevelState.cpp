#include "PlayerChangeLevelState.h"
#include "PlayerStandingState.h"
#include "Mario.h"
#include "Grid.h"
#include "EffectBigBang.h"
PlayerChangeLevelState::PlayerChangeLevelState(bool isdead,TYPE typeChange)
{
	player->vx = 0;
	auto effect = new EffectBigBang();
	if (player->level != SMALL)
	{
		player->level = typeChange;
		player->startTimeDead();
		switch (player->level)
		{
		case RACCOON:
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			grid->AddStaticObject(effect, player->x, player->y);
			isBig = false;
			break;
		case BIG:
			isBig = true;
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
			break;
		case FIRE:
			isBig = false;
			grid->AddStaticObject(effect, player->x, player->y);
			if (player->nx > 0)
				stateName = STANDING_RIGHT;
			else stateName = STANDING_LEFT;
			break;
		}
		
	}
	else {
		if (isdead)
		{
			upsize = false;
			stateName = DIE;
			player->isDead = true;
			player->vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			player->startTimeDead();
			player->level = BIG;
			isBig = false;
			upsize = true;
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
		}
	}

}


void PlayerChangeLevelState::Update(DWORD dt)
{
	if (GetTickCount() - player->untouchableTime > MARIO_UNTOUCHABLE_TIME && !player->isDead )
	{
		if (player->level == BIG  )
		{
			if (isBig)
			{
				player->freeze = true;
				player->level = SMALL;
			}
			else if (upsize)
			{
				player->freeze = true;
				player->level = BIG;
			}
				
		}
		player->ChangeAnimation(new PlayerStandingState());
		
	}
}