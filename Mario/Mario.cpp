#include "Mario.h"
#include "PlayerState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerFallingState.h"
#include "PlayerWalkingState.h"
#include "PlayerRunningState.h"
#include "PlayerSittingState.h"
#include "PlayerJumpingShortState.h"
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
	level = RACCOON;
}

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	GameObject::Update(dt);
	state->Update();
	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	//if (vy >= MARIO_GRAVITY * dt);

	if (vy > 3.5 * (MARIO_GRAVITY * dt))
	{
		ChangeAnimation(new PlayerFallingState());
	}
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
		
		if (ny == 1)
		{
			vy = 0;
			isJumpDone = true;
		}
		else if (ny == -1)
		{
			isJumping = false;
		}
		
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
					if (e->ny != 0)
					{
						vy = 0;
					}

				}
				else 
				{
					if (e->ny != 0)
					{
						vy = 0;
					}
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
		else if (stateBoundingBox == MARIO_STATE_BIG_BOUNDING_BOX)
		{
			left = x;
			top = y;
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
		else{
			left = x;
			top = y;
			right = x + 9;
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
			if (!isJumping && Allow[JUMPING_LONG])
			{
				startJump();
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
		case DIK_X:
		{
			if (!isJumping && Allow[JUMPING_SHORT])
			{
				if ((keyCode[DIK_RIGHT]))
				{
					nx = 1;
					ChangeAnimation(new PlayerJumpingShortState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					nx = -1;
					ChangeAnimation(new PlayerJumpingShortState());
				}
				else
				{
					ChangeAnimation(new PlayerJumpingShortState());
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
			
			break;
		}
		case DIK_1: 
			SetLevel(SMALL);
			ChangeAnimation(new PlayerStandingState());
			break;
		case DIK_2:
			SetLevel(BIG);
			ChangeAnimation(new PlayerStandingState());
			y -= 20;
			break;
		case DIK_3:
			SetLevel(RACCOON);
			ChangeAnimation(new PlayerStandingState());
			break;
		case DIK_F1:
			isOnSky = false;
			SetPosition(50, 400);
			break;
		case DIK_F2:
			isOnSky = false;
			SetPosition(900, 300);
			break;
		case DIK_F3:
			isOnSky = false;
			SetPosition(2500, 400);
			break;
		case DIK_F4:
			isOnSky = true;
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
		isJumpDone = true;
		player->canFallJump = true;
		break;
	case DIK_DOWN:
		//isSitting = false;
		break;
	case DIK_X:

		break;
	}
	
}
void Mario::Revival(float x, float y)
{
	ChangeAnimation(new PlayerStandingState());
	SetPosition(x, y);
	SetSpeed(0, 0);
	isOnSky = false;
}