#include "PlayerShootingFireState.h"
#include "PlayerStandingState.h"
#include "Mario.h"
PlayerShootingFireState::PlayerShootingFireState()
{

	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;

	if (!player->isShooting)
	{
		player->canShoot = true;
	}

	player->isShooting = true;
	if (!player->isJumping)
	{
		if (player->nx > 0) {
			stateName = STANDING_FIRE_RIGHT;
		}
		else {
			stateName = STANDING_FIRE_LEFT;
		}
	}
	else
	{
		if (player->nx > 0) {
			stateName = JUMPING_FIRE_RIGHT;
		}
		else {
			stateName = JUMPING_FIRE_LEFT;
		}
	}
	
}
void PlayerShootingFireState::HandleKeyBoard()
{

}
void PlayerShootingFireState::Update() 
{
	if (player->countShoot <= 1 && player->countShoot > 0)
	{
		player->canShoot = true;
		player->countShoot++;
	}
	else
	{
		player->canShoot = false;
	}
	
}

void PlayerShootingFireState::Render()
{
	if (player->CurAnimation->isLastFrame) {
		player->CurAnimation->isLastFrame = false;
		player->CurAnimation->currentFrame = -1;
		player->ChangeAnimation(new PlayerStandingState());
	}
}
PlayerShootingFireState::~PlayerShootingFireState(){}