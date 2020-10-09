#include "PlayerLastRunState.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
PlayerLastRunState::PlayerLastRunState() {
	player->allow[STANDING] = true;
	player->allow[WALKING] = true;
	player->isWalkingComplete = false;
	player->vx = 0;
	if (player->nx > 0) {
		stateName = LAST_RIGHT;
	}
	else {
		stateName = LAST_LEFT;
	}
}
PlayerLastRunState::~PlayerLastRunState(){}
void PlayerLastRunState::HandleKeyBoard() {
	
}
void PlayerLastRunState::Update() {

}