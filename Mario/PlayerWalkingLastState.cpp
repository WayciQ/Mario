#include "PlayerWalkingLastState.h"
#include "Mario.h"
#include "PlayerWalkingState.h"
#include "PlayerStandingState.h"
PlayerWalkingLastState::PlayerWalkingLastState() {
	if (player->vx > 0) {
		stateName = WALKING_RIGHT;
	}
	else stateName = WALKING_LEFT;
}
PlayerWalkingLastState::~PlayerWalkingLastState(){}
void PlayerWalkingLastState::Update(){}
void PlayerWalkingLastState::HandleKeyBoard(){}