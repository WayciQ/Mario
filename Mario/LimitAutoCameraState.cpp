#include "LimitAutoCameraState.h"
#include "PlayerWalkingState.h"
#include  "PlayerJumpingState.h"
#include  "PlayerSittingState.h"
#include "Mario.h"
#include "Camera.h"	
LimitAutoCameraState::LimitAutoCameraState()
{
	
	if (player->nx > 0) {
		stateName = WALKING_RIGHT;
	}
	else {
		stateName = WALKING_LEFT;
	}
	if (player->isSitting) {
		if (player->nx > 0) {
			stateName = SITTING_RIGHT;
		}
		else {
			stateName = SITTING_LEFT;
		}
	}
}

void LimitAutoCameraState::Update(DWORD dt)
{
	this->HandleKeyBoard();
	if (player->x < camera->cam_x) {
		player->x = camera->cam_x;
	}
	/*if (player->x > camera->cam_x + camera->GetWidth() - 32)
	{
		player->x = camera->cam_x + camera->GetWidth() - 48;
	}*/
}

void LimitAutoCameraState::Render()
{
}

void LimitAutoCameraState::HandleKeyBoard()
{
	if (keyCode[DIK_RIGHT]) {
		player->nx = 1;
		player->ChangeState(new PlayerWalkingState()	);
	}
	else if (keyCode[DIK_LEFT]) {
		player->nx = -1;
		player->ChangeState(new PlayerWalkingState());
	}
	else if (keyCode[DIK_S]) {
		player->ChangeState(new PlayerJumpingState());
	}
	else if (keyCode[DIK_DOWN] && player->Allow[SITTING]) {
		player->ChangeState(new PlayerSittingState());
	}
}
