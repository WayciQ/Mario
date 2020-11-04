#include "PlayerDieState.h"
#include "Mario.h"
PlayerDieState::PlayerDieState() 
{
	if (player->level == SMALL)
	{
		stateName = DIE;
	}
	else player->startTimeDead();

}