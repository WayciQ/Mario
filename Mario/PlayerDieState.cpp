#include "PlayerDieState.h"
#include "Mario.h"
PlayerDieState::PlayerDieState() {
	
	stateName = DIE;
	player->isDead = true;

}

void PlayerDieState::Update(DWORD dt) {

}
void PlayerDieState::HandleKeyBoard() {
	
}

void PlayerDieState::Render(){}
PlayerDieState::~PlayerDieState() {}