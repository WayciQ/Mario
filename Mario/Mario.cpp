#include "Mario.h"
#include "PlayerState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerFallingState.h"
#include "PlayerWalkingState.h"
#include "PlayerRunningState.h"
#include "PlayerSittingState.h"
#include "Goomba.h"

Mario* Mario:: __instance = NULL;
Mario* Mario::GetInstance()
{
	if (__instance == NULL)
		__instance = new Mario();
	return __instance;
}
Mario::Mario() {
	level = SMALL;
}
void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	GameObject::Update(dt);
	state->Update();
	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	isWaittingPressBtn = GetTickCount() - startWalkingComplete <= MARIO_LAST_RUN_TIME;
	/*if (isWaittingPressBtn) {
		DebugOut(L"\n isWaittingPress:true - %d", GetTickCount() - startWalkingComplete);
	}else DebugOut(L"\n isWaittingPress:false - %d", GetTickCount() - startWalkingComplete);*/
	
		
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

		if (nx != 0) 

		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Goomba*>(e->obj)) // if e->obj is Goomba 
			{
				Goomba* goomba = dynamic_cast<Goomba*>(e->obj);
				if (e->ny < 0)
				{
					if (!e->obj->isDead)
					{
						e->obj->isDead = true;
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::HandleObject(LPGAMEOBJECT object) {

}
void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == RACCOON || level == BIG) {
		if (stateBoundingBox == MARIO_STATE_BIG_SIT_BOUNDING_BOX) {
			left = x;
			top = y + MARIO_BIG_SIT_BBOX_HEIGHT;
			/*right = x + MARIO_BIG_SIT_BBOX_WIDTH;
			bottom = y + MARIO_BIG_SIT_BBOX_HEIGHT;*/
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT ;
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
	AnimationSets* ani_sets = AnimationSets::GetInstance();
	delete state;
	state = newState;
	LPANIMATION_SET ani = ani_sets->Get(level);
	state->stateName = newState->stateName;
	/*CurAnimation = animations[newState->stateName];*/
	CurAnimation = ani->Get(newState->stateName);
}



void Mario::OnKeyDown(int key)
{
	switch (key)
	{
		case DIK_S:
		{
			if (!isJumping && allow[JUMPING])
			{
				
				if ((keyCode[DIK_RIGHT]))
				{
					nx = 1;
					ChangeAnimation(new PlayerJumpingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
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
		
		case DIK_A:
		{
			if (!isWhipping && allow[WHIPPING]) {
				if (keyCode[DIK_RIGHT]) {
					nx = 1;
					ChangeAnimation(new PlayerWhippingState());
				}
				else if (keyCode[DIK_LEFT]) {
					nx = -1;
					ChangeAnimation(new PlayerWhippingState());
				}
				else 
				{
					ChangeAnimation(new PlayerWhippingState());
				}
			}
			break;
		}
		case DIK_DOWN:
		{
			/*if (!isSitting && allow[SITTING])
			{
				if (keyCode[DIK_RIGHT]) {
					nx = 1;
					ChangeAnimation(new PlayerWalkingState());
				}
				else if (keyCode[DIK_LEFT]) {
					nx = -1;
					ChangeAnimation(new PlayerWalkingState());
				}
				else
				{
					ChangeAnimation(new PlayerSittingState());
				}
			}*/
			break;
		}
		case DIK_1: 
			level = SMALL;
			y -= 20;
			break;
		case DIK_2:
			level = BIG;
			y -= 20;
			break;
		case DIK_3:
			level = RACCOON;
			y -= 20;
			break;
	}
}
void Mario::OnKeyUp(int key) {
	switch (key)
	{
	case DIK_A:
	{
		isWhipping = false;
		isRunning = false;
		break;
	}
	case DIK_RIGHT:
		startWalkingDone();
		walkingDirection = 1;
		break;
	case DIK_LEFT:
		startWalkingDone();
		walkingDirection = -1;
		break;
	case DIK_S:
		/*if (!isJumping && allow[JUMPING]) {
			ChangeAnimation(new PlayerFallingState());
		}*/
		break;
	case DIK_DOWN:
		//isSitting = false;
		break;
	}
	
}
void Mario::Reset(float x, float y)
{
	ChangeAnimation(new PlayerStandingState());
	SetPosition(x, y);
	SetSpeed(0, 0);
}