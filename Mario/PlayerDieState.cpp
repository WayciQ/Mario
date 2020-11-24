#include "PlayerDieState.h"
#include "PlayerStandingState.h"
#include "Mario.h"
PlayerDieState::PlayerDieState() 
{
	
	if (player->level != SMALL)
	{
		player->startTimeDead();
		switch (player->level)
		{
		case RACCOON:
			player->level = BIG;
			break;
		case BIG:
			stateName = player->nx > 0 ? DOWN_SIZE_RIGHT : DOWN_SIZE_LEFT;
			player->level = SMALL;
			break;
		case FIRE:
			stateName = player->nx > 0 ? UP_SIZE_RIGHT : UP_SIZE_LEFT;
			player->level = BIG;
			break;
		}
		if (player->nx > 0)
			stateName = STANDING_RIGHT;
		else stateName = STANDING_LEFT;
		
	}
	else {
		stateName = DIE;
		player->isDead = true;
		player->vx = 0;
		player->vy = -MARIO_JUMP_DEFLECT_SPEED;
	}

}


void PlayerDieState::Update(DWORD dt)
{
	if (GetTickCount() - player->untouchableTime < MARIO_UNTOUCHABLE_TIME)
	{
		player->ChangeAnimation(new PlayerStandingState());
	}
}