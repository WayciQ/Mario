#include "PlayerEndSceneState.h"
#include "PlayerStandingState.h"
#include "Mario.h"
#include "Map.h"
PlayerEndSceneState::PlayerEndSceneState() {
	player->Allow[WALKING] = false;
	player->Allow[JUMPING] = false;
	player->Allow[SITTING] = false;
	player->Allow[FALLING] = false;
	stateName = WALKING_RIGHT;
	player->vx = MARIO_WALKING_SPEED;

}
void PlayerEndSceneState::Update(DWORD dt) {
	if (player->x > map->GetWidthMap() - 48) {
		player->infor->SetSceneId(0);
		player->IsChangeScene = true;
	}
}