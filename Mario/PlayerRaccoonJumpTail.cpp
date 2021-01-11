#include "PlayerRaccoonJumpTail.h"
#include "PlayerFallingState.h"
#include "Mario.h"
PlayerRaccoonJumpTail::PlayerRaccoonJumpTail() {
	player->Allow[JUMPING] = false;
	//player->Allow[RACCON_WHIPING_FLY] = false;
	
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
	
	if (keyCode[DIK_S] && player->Allow[RACCON_WHIPING_FLY]) {
		player->vy = 0;
		player->ChangeState(new PlayerRaccoonJumpTail());
	}
	else {
		player->gravity = WORLD_GRAVITY;
		player->ChangeState(new PlayerFallingState());
	}
}
void PlayerRaccoonJumpTail::Render() {
}

PlayerRaccoonJumpTail::~PlayerRaccoonJumpTail() {}