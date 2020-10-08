#include "Mario.h"
#include "PlayerState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
Mario* Mario:: __instance = NULL;
Mario* Mario::GetInstance()
{
	if (__instance == NULL)
		__instance = new Mario();
	return __instance;
}
Mario::Mario() {
	level = MARIO_LEVEL_RACCOON;
}
void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	GameObject::Update(dt);
	state->Update();
	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	/*if(state->stateName != )*/
	CalcPotentialCollisions(coObjects, coEvents);
	
	//// reset untouchable timer if untouchable time has passed
	/*if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.3f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.3f;
		
		isJumping = false;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::HandleObject(LPGAMEOBJECT object) {

}
void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_RACCOON || level == MARIO_LEVEL_BIG) {
		if (stateBoundingBox == MARIO_STATE_BIG_SIT_BOUNDING_BOX) {
			left = x;
			top = y;
			right = x + MARIO_BIG_SIT_BBOX_WIDTH;
			bottom = y + MARIO_BIG_SIT_BBOX_HEIGHT;
		}
		else {
			left = x;
			top = y;
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else  {
		left = x;
		top = y;
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
	 
	
}

void Mario::Render() {
		alpha = 255;
		if (state->stateName == WHIPPING_LEFT) {
			CurAnimation->Render(x-10, y, alpha);
		}
		else {
			CurAnimation->Render(x, y, alpha);
		}
		
	RenderBoundingBox();
}
void Mario::ChangeAnimation(PlayerState* newState)
{
	delete state;
	state = newState;
	state->stateName = newState->stateName;
	CurAnimation = animations[newState->stateName];
}



void Mario::OnKeyDown(int key)
{
	switch (key)
	{
		case DIK_SPACE:
		{
			if (!isJumping && allow[JUMPING])
			{
				if ((keyCode[DIK_RIGHT]))
				{
					vx = MARIO_WALKING_SPEED;
					nx = 1;
					ChangeAnimation(new PlayerJumpingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					vx = -MARIO_WALKING_SPEED;
					nx = -1;
					ChangeAnimation(new PlayerJumpingState());
				}
				else
				{
					ChangeAnimation(new PlayerJumpingState());
				}
			}
			break;
		}
		case DIK_DOWN:
		{
			if (!isSitting && allow[SITTING]) {
				y += 11;
			}
			
			break;
		}
		case DIK_S:
		{
			if (!isWhipping && allow[WHIPPING]) {
				if (keyCode[DIK_RIGHT]) {
					vx = MARIO_WALKING_SPEED;
					nx = 1;
					DebugOut(L"W R1\n");
					ChangeAnimation(new PlayerWhippingState());
				}
				else if (keyCode[DIK_LEFT]) {
					vx = -MARIO_WALKING_SPEED;
					nx = -1;
					DebugOut(L"W L1\n");
					ChangeAnimation(new PlayerWhippingState());
				}
				else {
					ChangeAnimation(new PlayerWhippingState());
				}
			}
			break;
		}
	}
}
void Mario::OnKeyUp(int key) {
	switch (key) {
	case DIK_S:
	{
		player->isWhipping = false;
	}
	}
}