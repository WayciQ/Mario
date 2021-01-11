#include "PlayerRaccoonJumpTail.h"
#include "PlayerFallingState.h"
#include "Mario.h"
PlayerRaccoonJumpTail::PlayerRaccoonJumpTail() {
	player->Allow[JUMPING] = false;
	player->Allow[RACCON_WHIPING_FLY] = false;
	player->gravity = 0.0001f;
	if (player->nx > 0) {
		stateName = RACCON_WHIPING_FLY_RIGHT;
	}
	else {
		stateName = RACCON_WHIPING_FLY_LEFT;
	}
	player->isWavingTail = true;
}

void PlayerRaccoonJumpTail::Update(DWORD dt) {
	this->HandleKeyBoard();
}

void PlayerRaccoonJumpTail::HandleKeyBoard() {
	if (!keyCode[DIK_S]) {
		player->gravity = WORLD_GRAVITY;
		player->ChangeState(new PlayerFallingState());
	}
}
void PlayerRaccoonJumpTail::Render() {
}

PlayerRaccoonJumpTail::~PlayerRaccoonJumpTail() {}