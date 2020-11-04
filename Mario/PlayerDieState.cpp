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
			player->level = SMALL;
			break;
		case FIRE:
			player->level = BIG;
			break;
		}
		if (player->nx > 0)
			stateName = STANDING_RIGHT;
		else stateName = STANDING_LEFT;
		player->ChangeAnimation(new PlayerStandingState());
	}
	else {
		stateName = DIE;
		player->isDead = true;
		player->vx = 0;
		player->vy = -MARIO_JUMP_DEFLECT_SPEED;
	}

}

void PlayerDieState::Render()
{

}

void PlayerDieState::Update()
{

}