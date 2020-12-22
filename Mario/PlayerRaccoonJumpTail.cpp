#include "PlayerRaccoonJumpTail.h"
#include "PlayerFallingState.h"
#include "Mario.h"
PlayerRaccoonJumpTail::PlayerRaccoonJumpTail() {

	player->gravity = 0.00001f;
	if (player->nx > 0) {
		stateName = RACCON_WHIPING_FLY_RIGHT;
	}
	else {
		stateName = RACCON_WHIPING_FLY_LEFT;
	}
	timeWaving = GetTickCount();
}

void PlayerRaccoonJumpTail::Update(DWORD dt) {
	this->HandleKeyBoard();
	if (GetTickCount() - timeWaving >= 5550) {
		player->ChangeState(new PlayerFallingState());
		player->Allow[WAVING_TAIL] = false;
	}
}

void PlayerRaccoonJumpTail::HandleKeyBoard() {
	if (keyCode[DIK_S]) {
		player->ChangeState(new PlayerRaccoonJumpTail());
	}
}
void PlayerRaccoonJumpTail::Render() {
	
}

PlayerRaccoonJumpTail::~PlayerRaccoonJumpTail() {}