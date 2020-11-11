#include "Mario.h"
#include "PlayerState.h"
#include "PlayerKickState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerFallingState.h"
#include "PlayerWalkingState.h"
#include "PlayerRunningState.h"
#include "PlayerSittingState.h"
#include "PlayerJumpingShortState.h"
#include "PlayerShootingFireState.h"
#include "PlayerDieState.h"
#include "Goomba.h"
#include "PlayerHoldingState.h"

Mario* Mario:: __instance = NULL;
Mario* Mario::GetInstance()
{
	if (__instance == NULL)
		__instance = new Mario();
	return __instance;
}
Mario::Mario() {
	tag = PLAYER;
	type = MARIO;
	level = BIG;
}

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	GameObject::Update(dt);
	state->Update();
	// Simple fall down
	vy += WORLD_GRAVITY * dt;
	//DebugOut(L"state: %d\n", player->GetState());
	
	if(y > curY)
	{
		ChangeAnimation(new PlayerFallingState());
	}
	isWaittingPressBtn = GetTickCount() - startWalkingComplete <= MARIO_LAST_RUN_TIME;
	/*if (isWaittingPressBtn) {
		DebugOut(L"\n isWaittingPress:true - %d", GetTickCount() - startWalkingComplete);
	}else DebugOut(L"\n isWaittingPress:false - %d", GetTickCount() - startWalkingComplete);*/
	
	if (GetTickCount() - untouchableTime >= MARIO_UNTOUCHABLE_TIME)
	{
		untouchableTime = 0;
		untouchable = false;
	}

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
		y += min_ty * dy + ny * 0.1f;
		
		if (ny == 1)
		{
			vy = 0;
			isJumpDone = true;
		}
		else if (ny == -1)
		{
			isJumping = false;
			curY = y;
		}
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			switch (e->obj->tag)
			{
			case GROUND:
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
				if (e->obj->type == BRICK_QUESTION)
				{
					if (e->ny == 1)
					{
						vy = 0;
						e->obj->isDead = true;
					}

				}
				break;
			case ENEMY:
				if (e->ny == -1)
				{
					if (e->obj->type == KOOMBA && e->obj->isDead)
					{
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						if (e->obj->isKicked)
						{
							e->obj->isKicked = false;
							e->obj->vx = 0;
							if (e->obj->isFlip)
							{
								SetState(ENEMY_DIE_FLIP);
							}
							else SetState(ENEMY_DIE_STAND);
						}
						else {
							ChangeAnimation(new PlayerKickState());
							e->obj->isKicked = true;
							e->obj->canRespawn = false;
							if (player->nx > 0)
							{
								e->obj->vx = 2 * MARIO_WALKING_SPEED;
							}
							else {
								e->obj->vx = -2 * MARIO_WALKING_SPEED;
							}
						}
					}
					else {
						if (e->obj->type == KOOMBA || e->obj->type == GOOMBA)
						{
							if (!e->obj->isDead)
							{
								e->obj->vx = 0;
								vy = -MARIO_JUMP_DEFLECT_SPEED;
							}
							e->obj->startTimeDead();
							e->obj->isFlip = false;
							e->obj->SetState(ENEMY_DIE_STAND);
						}
						else {
							startTimeDead();
							y += dy;
						}
					}
				}
				if (e->nx != 0)
				{
					if (!untouchable)
					{
						if (!e->obj->isDead) {
							ChangeAnimation(new PlayerDieState());
						}
						else {
							if (e->obj->type == KOOMBA)
							{
								if (e->obj->isKicked && e->obj->vx != 0)
								{
									startTimeDead();
								}
								if (canHolding) {
									isHolding = true;
								}
								else {
									if (!e->obj->isKicked && e->nx != player->nx)
									{
										ChangeAnimation(new PlayerKickState());
										e->obj->isDead = true;
										e->obj->isKicked = true;
										e->obj->canRespawn = false;
										if (player->nx > 0)
										{
											e->obj->vx = 2 * MARIO_WALKING_SPEED;
										}
										else {
											e->obj->vx = -2 * MARIO_WALKING_SPEED;
										}
									}
									
								}
								
								
							}
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == RACCOON || level == BIG || level == FIRE) {
		
		if (level != RACCOON)
		{
			if (stateBoundingBox == MARIO_STATE_BIG_SIT_BOUNDING_BOX && isSitting) {
				left = x;
				top = y + MARIO_BIG_SIT_BBOX_TOP;
				right = x + MARIO_BIG_BBOX_WIDTH;
				bottom = y + MARIO_BIG_BBOX_HEIGHT;
			}
			else if (stateBoundingBox == MARIO_STATE_BIG_BOUNDING_BOX)
			{
				if (level == RACCOON)
				{
					left = x + MARIO_RACCOON_FIGHT_WIDTH_X;
					top = y;
					right = x + MARIO_BIG_BBOX_WIDTH + MARIO_RACCOON_FIGHT_WIDTH_X;
					bottom = y + MARIO_BIG_BBOX_HEIGHT;
				}
				else
				{
					left = x;
					top = y;
					right = x + MARIO_BIG_BBOX_WIDTH;
					bottom = y + MARIO_BIG_BBOX_HEIGHT;
				}
			}
		}
		else
		{
			if (stateBoundingBox == MARIO_STATE_BIG_SIT_BOUNDING_BOX && isSitting) {
				if (nx < 0)
				{
					left = x;
					top = y + MARIO_BIG_SIT_BBOX_TOP;
					right = x + MARIO_BIG_BBOX_WIDTH;
					bottom = y + MARIO_BIG_BBOX_HEIGHT;
				}
				else
				{
					left = x + MARIO_RACCOON_FIGHT_WIDTH_X;
					top = y + MARIO_BIG_SIT_BBOX_TOP;
					right = x +MARIO_RACCOON_FIGHT_WIDTH_X + MARIO_BIG_BBOX_WIDTH;
					bottom = y + MARIO_BIG_BBOX_HEIGHT;
				}
				
			}
			else if (stateBoundingBox == MARIO_STATE_BIG_BOUNDING_BOX)
			{
				if (nx < 0)
				{
					left = x;
					top = y;
					right = x + MARIO_BIG_BBOX_WIDTH ;
					bottom = y + MARIO_BIG_BBOX_HEIGHT;
				}
				else
				{
					left = x + MARIO_RACCOON_FIGHT_WIDTH_X;
					top = y;
					right = x + MARIO_BIG_BBOX_WIDTH + MARIO_RACCOON_FIGHT_WIDTH_X;
					bottom = y + MARIO_BIG_BBOX_HEIGHT;
				}
			}
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
		state->Render();
		if (untouchable)
		{
			alpha = alpha == 255 ? 125 : 255;
		}
		else alpha = 255;
	CurAnimation->Render(x, y, alpha);
	RenderBoundingBox();
}
void Mario::ChangeAnimation(PlayerState* newState)
{
	delete state;
	state = newState;
	LPANIMATION_SET ani = animationsSets->Get(level);
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
		{	startJump();
			if (!isJumping && Allow[JUMPING_SHORT])
			{
				if ((keyCode[DIK_RIGHT]))
				{
					nx = 1;
					ChangeAnimation(new PlayerJumpingState());
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
			
			switch (level)
			{
			case RACCOON:
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
			case FIRE:
				if (!isShooting && Allow[FIRING_FIRE]) {
					{
						ChangeAnimation(new PlayerShootingFireState());
					}
				}
				break;
			}
			if (!canHolding)
			{
				canHolding = true;
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
			y -= 20;
			SetLevel(RACCOON);
			ChangeAnimation(new PlayerStandingState());
			break;
		case DIK_4:
			y -= 20;
			SetLevel(FIRE);
			ChangeAnimation(new PlayerStandingState());
			break;
		case DIK_F1:
			isOnSky = false;
			SetPosition(0,0);
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
		canHolding = false;
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