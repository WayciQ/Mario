
#include "Mario.h"
#include "PlayerState.h"
#include "PlayerKickState.h"
#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerWhippingState.h"
#include "PlayerFallingState.h"
#include "PlayerWalkingState.h"
#include "PlayerSittingState.h"
#include "PlayerShootingFireState.h"
#include "PlayerChangeLevelState.h"
#include "PlayerFlyingState.h"
#include "PlayerWorlMapState.h"
#include "Goomba.h"
#include "PlayerHoldingState.h"
#include "Portal.h"
#include "Trigger.h"
#include "Camera.h"
#include "CheckPoint.h"
#include "Card.h"
#include "PlayerEndSceneState.h"
#include "PlayerRaccoonJumpTail.h"
Mario * Mario::__instance = NULL;
Mario* Mario::GetInstance()
{
	if (__instance == NULL)
		__instance = new Mario();
	return __instance;
}

Mario::Mario() {
	tag = PLAYER;
	type = MARIO;
	level = SMALL;
	gravity = WORLD_GRAVITY;
	infor = new Information();
}

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	GameObject::Update(dt);
	state->Update(dt);
	// Simple fall down
	vy += gravity * dt;
	//DebugOut(L"state: %d\n", player->GetState());

	/*if(y > curY+15)
	{
		ChangeState(new PlayerFallingState());
	}*/
	isWaittingPressBtn = GetTickCount() - startWalkingComplete <= MARIO_LAST_RUN_TIME;
	/*if (isWaittingPressBtn) {
		DebugOut(L"\n isWaittingPress:true - %d", GetTickCount() - startWalkingComplete);
	}else DebugOut(L"\n isWaittingPress:false - %d", GetTickCount() - startWalkingComplete);*/

	if (GetTickCount() - untouchableTime >= MARIO_UNTOUCHABLE_TIME)
	{
		untouchableTime = 0;
		untouchable = false;
	}

	if (GetTickCount() - countTime > 1000 && !freeze)
	{
		infor->CalcTimeGame(-1);
		countTime = GetTickCount();
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	//DebugOut(L"x: %f\ny:%f\n", x, y);
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


		if (ny == -1)
		{
			vy = 0;
			isOnSky = false;
			curY = y;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			switch (e->obj->tag)
			{
			case GROUND:
				UpdateWithGround(e);
				break;
			case ENEMY:
				if (!untouchable)UpdateWithEnemy(e);
				break;
			case ITEM:
				UpdateWithItem(e);
				break;
			case BOX:
				UpdateWithGate(e);
				break;
			}

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::UpdateWithEnemy(LPCOLLISIONEVENT e)
{
	if (e->ny == -1)
	{
		if (!e->obj->isDead)
		{
			if (e->obj->typeParent != PLANT)
			{
				e->obj->vx = 0;
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				e->obj->startTimeDead();
				e->obj->isFlip = false;
				e->obj->SetState(ENEMY_DIE_STAND);
				infor->ScoreEarn(100);
			}
			else {
				ChangeState(new PlayerChangeLevelState(true, level));
				y += dy;
			}
		}
		else
		{
			if (e->obj->typeParent == KOOMPA)
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
					infor->ScoreEarn(100);
				}
				else {
					ChangeState(new PlayerKickState());
					e->obj->isKicked = true;
					e->obj->canRespawn = false;
					e->obj->tagChange = WEAPON;
					if (player->nx > 0)
					{
						e->obj->vx = 2 * MARIO_WALKING_SPEED;
					}
					else {
						e->obj->vx = -2 * MARIO_WALKING_SPEED;
					}
					infor->ScoreEarn(100);
				}
			}
		}
	}
	if (e->nx != 0)
	{
		if (!untouchable)
		{
			if (!e->obj->isDead) {
				ChangeState(new PlayerChangeLevelState(true, level));
			}
			else {
				if (e->obj->typeParent == KOOMPA)
				{
					if (e->obj->isKicked && e->obj->vx != 0)
					{
						ChangeState(new PlayerChangeLevelState(true, level));
					}
					if (canPicking) {
						isPicking = true;
					}
					else {
						if (!e->obj->isKicked && e->nx != player->nx)
						{
							ChangeState(new PlayerKickState());
							e->obj->isDead = true;
							e->obj->isKicked = true;
							e->obj->tagChange = WEAPON;
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
	if (e->ny == 1)
	{
		ChangeState(new PlayerChangeLevelState(true, level));
	}
}
void Mario::UpdateWithItem(LPCOLLISIONEVENT e)
{ 
	e->obj->isDead = true;
	e->obj->canDel = true;
	switch (e->obj->type)
	{
	case LEAF:
		ChangeState(new PlayerChangeLevelState(false, RACCOON));
		break;
	case COIN:
		infor->ScoreEarn(100);
		infor->MoneyEarn(1);
		break;
	case RED_MUSHROOM:
		ChangeState(new PlayerChangeLevelState(false, BIG));
		break;
	case GREEN_MUSHROOM:
		infor->LifeEarn(1);
		break;
	}
}
void Mario::UpdateWithGround(LPCOLLISIONEVENT e)
{
	if (e->ny == 1) {
		vy = 0;
		isJumpDone = true;
	}
	switch (e->obj->type)
	{
	case GROUND_BOX:
		if (e->nx != 0)
		{
			x += dx;
		}
		if (e->ny != 0)
		{
			vy = 0;
		}
		break;
	case BLOCK_QUESTION: case BLOCK_BREAKABLE:
		if (e->ny == 1)
		{
			vy = 0;
			e->obj->isDead = true;
			infor->ScoreEarn(20);
		}
	default:
		break;
	}
	

	
	if (dynamic_cast<Card*>(e->obj)) {
		e->obj->isDead = true;
		e->obj->canDel = true;
		Card* card = dynamic_cast<Card*>(e->obj);
		infor->AddCard(card->GetTypeCard());
		ChangeState(new PlayerEndSceneState());
	}
}
void Mario::UpdateWithGate(LPCOLLISIONEVENT e)
{
	x += dx;
	y += dy;

	if (IsCollisionAABB(GetRect(), e->obj->GetRect()))
	{

		if (dynamic_cast<Portal*>(e->obj))
		{
			y += dy;
			x += dx;
			Portal* p = dynamic_cast<Portal*>(e->obj);
			scene_id = p->GetSceneId();
			IsTouchPort = true;
			x = e->obj->x;
			y = e->obj->y;
			vx = 0;
			vy = 0;
		}
		else if (dynamic_cast<SceneGate*>(e->obj))
		{
			vx = 0;
			vy = 0;
			x += dx;
			SceneGate* p = dynamic_cast<SceneGate*>(e->obj);
			gateScene = p->GetTriggerPort();
			moveToTrigger = p->GetWayIn();
			IsTouchTrigger = true;
		}
		else if (dynamic_cast<CheckPoint*>(e->obj))
		{
			vx = 0;
			vy = 0;
			x = e->obj->x;
			y = e->obj->y;
			IsTouchPort = false;
		}
	}
}
void Mario::ChangeScene(int port)
{
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
			else if (stateBoundingBox == MARIO_STATE_SMALL_BOUDING_BOX)
			{
				left = x;
				top = y;
				right = x + MARIO_SMALL_BBOX_WIDTH;
				bottom = y + MARIO_SMALL_BBOX_HEIGHT;
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
					right = x + MARIO_RACCOON_FIGHT_WIDTH_X + MARIO_BIG_BBOX_WIDTH;
					bottom = y + MARIO_BIG_BBOX_HEIGHT;
				}

			}
			else if (stateBoundingBox == MARIO_STATE_BIG_BOUNDING_BOX)
			{
				if (nx < 0)
				{
					left = x;
					top = y;
					right = x + MARIO_BIG_BBOX_WIDTH;
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
			else if (stateBoundingBox == MARIO_STATE_SMALL_BOUDING_BOX)
			{
				left = x;
				top = y;
				right = x + MARIO_SMALL_BBOX_WIDTH;
				bottom = y + MARIO_SMALL_BBOX_HEIGHT;
			}

		}

	}
	else {
		left = x;
		top = y;
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}

}
#define MARIO_X_WHIP x - 9
void Mario::Render() {
	state->Render();
	if (untouchable)
	{
		alpha = alpha == 255 ? 125 : 255;
	}
	else alpha = 255;

	if (GetState() == WHIPPING_LEFT)
	{
		CurAnimation->Render(MARIO_X_WHIP, y, alpha);
	}
	else
	{
		CurAnimation->Render(x, y, alpha);
	}

	RenderBoundingBox();
}
void Mario::ChangeState(PlayerState* newState)
{
	delete state;
	state = newState;
	LPANIMATION_SET ani = animationsSets->Get(level);
	state->stateName = newState->stateName;
	CurAnimation = ani->Get(newState->stateName);
}


void Mario::OnKeyDown(int key)
{
	if (typeScene != PLAYER_IN_WORLD_MAP)
	{
		switch (key)
		{
		case DIK_S:
		{
			if (!isOnSky && Allow[JUMPING])
			{
				startJump();
				if ((keyCode[DIK_RIGHT]))
				{
					nx = 1;
					ChangeState(new PlayerJumpingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					nx = -1;
					ChangeState(new PlayerJumpingState());
				}
				else
				{
					ChangeState(new PlayerJumpingState());
				}
			}

			if (!isOnSky && Allow[FLYING])
			{
				StartTimeFly();
				if ((keyCode[DIK_RIGHT]))
				{
					nx = 1;
					ChangeState(new PlayerFlyingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					nx = -1;
					ChangeState(new PlayerFlyingState());
				}
				else
				{
					ChangeState(new PlayerFlyingState());
				}
			}
			if (player->Allow[RACCON_WHIPING_FLY])
			{
				if ((keyCode[DIK_RIGHT]))
				{
					player->nx = 1;
					player->ChangeState(new PlayerRaccoonJumpTail());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					player->nx = -1;
					player->ChangeState(new PlayerRaccoonJumpTail());
				}
				else
				{
					player->ChangeState(new PlayerRaccoonJumpTail());
				}
			}
			break;
		}
		case DIK_X:
		{
			if (!isOnSky && Allow[FLYING])
			{
				StartTimeFly();
				if ((keyCode[DIK_RIGHT]))
				{
					nx = 1;
					ChangeState(new PlayerFlyingState());
				}
				else if ((keyCode[DIK_LEFT]))
				{
					nx = -1;
					ChangeState(new PlayerFlyingState());
				}
				else
				{
					ChangeState(new PlayerFlyingState());
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
						ChangeState(new PlayerWhippingState());
					}
					else if (keyCode[DIK_LEFT]) {
						nx = -1;
						ChangeState(new PlayerWhippingState());
					}
					else
					{
						ChangeState(new PlayerWhippingState());
					}
				}
				break;
			case FIRE:
				if (!isShooting && Allow[FIRING_FIRE]) {
					{
						ChangeState(new PlayerShootingFireState());
					}
				}
				break;
			}
			if (!canPicking)
			{
				canPicking = true;
			}
			break;
		}
		case DIK_DOWN:
		{
			if (IsTouchTrigger && moveToTrigger == 1)
			{
				IsChangeTrigger = true;
				IsTouchTrigger = false;
			}
			break;
		}
		case DIK_1:
		{
			SetLevel(SMALL);
			ChangeState(new PlayerStandingState());
			break;
		}
		case DIK_2:
		{
			SetLevel(BIG);
			ChangeState(new PlayerStandingState());
			y -= 20;
			break;
		}
		case DIK_3:
		{
			y -= 20;
			SetLevel(RACCOON);
			ChangeState(new PlayerStandingState());
			break;
		}
		case DIK_4:
		{
			y -= 20;
			SetLevel(FIRE);
			ChangeState(new PlayerStandingState());
			break;
		}
		case DIK_F1:
		{
			SetPosition(70, 250);
			break;
		}
		case DIK_F2:
		{
			SetPosition(900, 300);
			break;
		}
		case DIK_F3:
		{
			SetPosition(2500, 400);
			break;
		}
		case DIK_F4:
		{
			SetPosition(1616, 140);
			break;
		}
		}
	}
	else
	{
		if (keyCode[DIK_LEFT])
		{
			player->ChangeState(new PlayerWorlMapState(-1));
		}
		else if (keyCode[DIK_RIGHT])
		{
			player->ChangeState(new PlayerWorlMapState(1));
		}
		else if (keyCode[DIK_UP])
		{
			player->ChangeState(new PlayerWorlMapState(-2));
		}
		else if (keyCode[DIK_DOWN])
		{
			player->ChangeState(new PlayerWorlMapState(2));
		}
		else if (keyCode[DIK_S])
		{
			if (IsTouchPort)
			{
				IsChangeScene = true;
				IsTouchPort = false;
			}
		}
	}
}
void Mario::OnKeyUp(int key) {
	if (typeScene != PLAYER_IN_WORLD_MAP)
	{
		switch (key)
		{
		case DIK_A:
		{
			isWhipping = false;
			canPicking = false;
			isRunning = false;
			player->Allow[RUNNING] = false;
			break;
		}
		case DIK_RIGHT:
		{
			startWalkingDone();
			walkingDirection = 1;
			break;
		}
		case DIK_LEFT:
		{
			startWalkingDone();
			walkingDirection = -1;
			break;
		}
		case DIK_S:
		{
			if (isJumping) {
				isJumpDone = true;
			}
			if(level == RACCOON && !isFlying && !isWavingTail)
				Allow[RACCON_WHIPING_FLY] = true;
			
			break;
		}
		case DIK_DOWN:
			break;
		case DIK_X:
			break;
		}
	}


}
void Mario::Revival(float x, float y, int isInScene)
{
	if (isInScene > 0)
	{
		gravity = WORLD_GRAVITY;
		nx = 1;
		ChangeState(new PlayerStandingState());
		typeScene = level;
	}
	else
	{
		ChangeState(new PlayerWorlMapState(0));
		typeScene = PLAYER_IN_WORLD_MAP;
	}
	SetPosition(x, y);
	SetSpeed(0, 0);
	freeze = false;
}
