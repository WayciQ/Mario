#include "PlayerWhippingState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "PlayerJumpingState.h"
#include "PlayerFallingState.h"
#include "Mario.h"

void PlayerWhippingState::Update() {
	
	this->HandleKeyBoard();
		if (player->CurAnimation->isLastFrame ) {
			player->Allow[WHIPPING] = true;
			player->CurAnimation->isLastFrame = false;
			player->CurAnimation->currentFrame = -1;
			player->ChangeAnimation(new PlayerStandingState());
		}
		
		
}
void PlayerWhippingState::HandleKeyBoard() {
	
}
PlayerWhippingState::PlayerWhippingState() {
	PrevState = player->state->stateName;
	player->Allow[JUMPING_LONG] = true;
	player->Allow[WALKING] = true;
	player->Allow[SITTING] = false;
	player->isWhipping = true;
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	if (player->nx > 0) {
		stateName = WHIPPING_RIGHT;
	}
	else {
		stateName = WHIPPING_LEFT;
	}
}
PlayerWhippingState::~PlayerWhippingState(){}