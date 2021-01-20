#include "PlayerEndSceneState.h"
#include "PlayerStandingState.h"
#include "Mario.h"
#include "camera.h"
PlayerEndSceneState::PlayerEndSceneState() {
	player->Allow[WALKING] = false;
	player->Allow[JUMPING] = false;
	player->Allow[SITTING] = false;
	player->Allow[FALLING] = false;
	stateName = WALKING_RIGHT;
	player->vx = MARIO_WALKING_SPEED;

}
void PlayerEndSceneState::Update(DWORD dt) {
	float cam_x, y;
	camera->GetCamPos(cam_x, y);
	if (player->x > cam_x + SCREEN_WIDTH) {
		player->infor->SetSceneId(0);
		player->IsChangeScene = true;
	}
}