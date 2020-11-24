#include "PlayerKickState.h"
#include "PlayerStandingState.h"
#include "Mario.h"

PlayerKickState::PlayerKickState()
{
	player->isKicking = true;
	player->stateBoundingBox = MARIO_STATE_BIG_BOUNDING_BOX;
	if (player->nx > 0)
	{
		stateName = KICKING_RIGHT;
	}
	else stateName = KICKING_LEFT;
}
void PlayerKickState::HandleKeyBoard()
{

}
void PlayerKickState::Update(DWORD dt)
{
	
}
void PlayerKickState::Render()
{
	if (player->CurAnimation->isLastFrame) {
		player->CurAnimation->isLastFrame = false;
		player->CurAnimation->currentFrame = -1;
		player->ChangeAnimation(new PlayerStandingState());
	}
}