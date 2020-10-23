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
	type = MARIO;
	level = BIG;
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

	
	CalcPotentialCollisions(coObjects, coEvents);
	

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
		x += min_tx * dx + nx * 0.1f;		
		y += min_ty * dy + ny * 0.3f;
		DebugOut(L"vx %f\n", vx);
		
		isJumping = false;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->tag = GROUND)
			{
				if (e->obj->type == BOX_GROUND)
				{
					if (e->nx != 0)
					{
						x += dx;
					}
				}
				else 
				{
					if (e->ny != 0)
						vy = 0;
					
				}
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == RACCOON || level == BIG) {
		if (stateBoundingBox == MARIO_STATE_BIG_SIT_BOUNDING_BOX && isSitting) {
			left = x;
			top = y + 2*MARIO_BIG_SIT_BBOX_HEIGHT;
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
		/*if (state->stateName == WHIPPING_LEFT) {
			CurAnimation->Render(x-10, y, alpha);
		}
		else */
			CurAnimation->Render(x, y, alpha);
		
		
	RenderBoundingBox();
}
void Mario::ChangeAnimation(PlayerState* newState)
{
	AnimationSets* ani_sets = AnimationSets::GetInstance();
	delete state;
	state = newState;
	LPANIMATION_SET ani = ani_sets->Get(level);
	state->stateName = newState->stateName;
	CurAnimation = ani->Get(newState->stateName);
}



void Mario::OnKeyDown(int key)
{
	switch (key)
	{
		case DIK_S:
		{
			if (!isJumping && Allow[JUMPING])
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
			if (!isWhipping && Allow[WHIPPING]) {
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
			ChangeAnimation(new PlayerStandingState());
			break;
		case DIK_2:
			level = BIG;
			ChangeAnimation(new PlayerStandingState());
			y -= 20;
			break;
		case DIK_3:
			level = RACCOON;
			ChangeAnimation(new PlayerStandingState());
			break;
		case DIK_F1:
			SetPosition(100, 400);
			break;
		case DIK_F2:
			SetPosition(1400, 400);
			break;
		case DIK_F3:
			SetPosition(2500, 400);
			break;
		case DIK_F4:
			SetPosition(1616, 140);
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