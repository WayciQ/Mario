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
#include "Alert.h"
#include "Grid.h"
#include "Effects.h"
Mario * Mario::__instance = NULL;
Mario* Mario::GetInstance()
{
	if (__instance == NULL)
		__instance = new Mario();
	return __instance;
}
#define EFFECT_SCORE_100 {auto ef = Effects::CreateEffect(SCORE_100);grid->AddMovingObject(ef, e->obj->x, e->obj->y);}
				
Mario::Mario() {
	tag = PLAYER;
	type = MARIO;
	level = SMALL;
	gravity = WORLD_GRAVITY;
	infor = new Information();
	immortal = false;
	countShoot = 0;
}
#define LENGTH_FALL currentLocationY + 15
#define TIME 1000
#define SCORE_1 100
#define SPEED_KICK_KOOMPA 0.6

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	GameObject::Update(dt);
	state->Update(dt);
	// Simple fall down
	vy += gravity * dt;
	
	//DebugOut(L"state: %d\n", player->GetState());
	//DebugOut(L"count: %d\n", countShoot);
	if(y > LENGTH_FALL && Allow[FALLING])
	{
		Allow[FALLING] = false;
		ChangeState(new PlayerFallingState());
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

	if (GetTickCount() - countRealTime > TIME && !isFreezeTime)
	{
		infor->CalcTimeGame(-1);
		countRealTime = GetTickCount();
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	//DebugOut(L"x: %f\ny:%f\n", x, y);
	CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (IsCollisionAABB(GetRect(), coObjects->at(i)->GetRect()))
			{
				CollisionAtCreate(coObjects->at(i));
			}
		}
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		// block 
		x += min_tx * dx + nx * 0.8f;
		//y += min_ty * dy + ny * 0.8f;
		if (ny == -1) {
			currentLocationY = y;
			isOnSky = false;
			Allow[RACCON_WHIPING_FLY] = false;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			switch (e->obj->tag)
			{
			case ITEM:
				UpdateWithItem(e);
				break;
			case GROUND:
				UpdateWithGround(e);
				break;
			case ENEMY:
				UpdateWithEnemy(e);
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
#define EFFECT_Y_SCORE y + 59
#define EFFECT_X_SCORE y + 59
void Mario::UpdateWithEnemy(LPCOLLISIONEVENT e)
{
	if (e->ny == -1)
	{
		if (!e->obj->isDead)
		{
			if (e->obj->typeParent == PLANT || e->obj->tagChange == WEAPON)
			{
				if (!untouchable) {
					if (!immortal) {
						ChangeState(new PlayerChangeLevelState(true));
					}
				}
			}
			else {
				e->obj->vx = 0;
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				e->obj->startTimeDead();
				e->obj->isFlip = false;
				e->obj->SetState(ENEMY_DIE_STAND);
				infor->ScoreEarn(SCORE_1);
				EFFECT_SCORE_100
			}
		}
		else
		{
			if (e->obj->typeParent == KOOMPA)
			{
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				if (e->obj->isKicked)
				{
					e->obj->startTimeDead();
					e->obj->isKicked = false;
					e->obj->vx = 0;
					if (e->obj->isFlip)
					{
						SetState(ENEMY_DIE_FLIP);
					}
					else SetState(ENEMY_DIE_STAND);
					infor->ScoreEarn(SCORE_1);
					auto ef = Effects::CreateEffect(SCORE_100);
					grid->AddMovingObject(ef, e->obj->x, e->obj->y);

				}
				else {
					ChangeState(new PlayerKickState());
					e->obj->isKicked = true;
					e->obj->canRespawn = false;
					e->obj->tagChange = WEAPON;
					if (player->nx > 0)
					{
						e->obj->vx = SPEED_KICK_KOOMPA;
					}
					else {
						e->obj->vx = -SPEED_KICK_KOOMPA;
					}
					infor->ScoreEarn(SCORE_1);
					EFFECT_SCORE_100
				}
			}
		}
	}
	else if (e->ny == 1)
	{
		vy = 0;
		if (!e->obj->isDead) {
			//vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (!untouchable) {
				if (!immortal) {
					ChangeState(new PlayerChangeLevelState(true));
				}
			}
		}
		else
		{
			if (e->obj->typeParent == KOOMPA)
			{
				ChangeState(new PlayerKickState());
				e->obj->isKicked = true;
				e->obj->canRespawn = false;
				e->obj->tagChange = WEAPON;
				if (player->nx > 0)
				{
					e->obj->vx = SPEED_KICK_KOOMPA;
				}
				else {
					e->obj->vx = -SPEED_KICK_KOOMPA;
				}
				infor->ScoreEarn(SCORE_1);
				EFFECT_SCORE_100
				
			}
		}
	}
	if (e->nx != 0)
	{
		x += dx;
		if (!e->obj->isDead) {
			if (!untouchable) {
				if (!immortal) {
					ChangeState(new PlayerChangeLevelState(true));
				}
			}
		}
		else {
			if (e->obj->typeParent == KOOMPA)
			{
				if (e->obj->isKicked && e->obj->vx != 0)
				{
					if (!untouchable) {
						if (!immortal)
							ChangeState(new PlayerChangeLevelState(true));
					}
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
							e->obj->vx = SPEED_KICK_KOOMPA;
						}
						else {
							e->obj->vx = -SPEED_KICK_KOOMPA;
						}
					}
				}
			}
		}
	}
}
void Mario::CollisionAtCreate(LPGAMEOBJECT obj)
{
	if (obj->tag == ITEM) {
		switch (obj->type)
		{
		case LEAF:
			if (level != RACCOON) {
				ChangeState(new PlayerChangeLevelState(false, RACCOON));
			}
			break;
		}
		obj->isDead = true;
	}
}
void Mario::UpdateWithItem(LPCOLLISIONEVENT e)
{
	switch (e->obj->type)
	{
	case LEAF:
		if (level != RACCOON) {
			ChangeState(new PlayerChangeLevelState(false,RACCOON));
		}
		else {
			EFFECT_SCORE_100
		}
		break;
	case COIN:
		//y += dy;
		infor->ScoreEarn(100);
		infor->MoneyEarn(1);
		break;
	case RED_MUSHROOM:
		if (level == SMALL) {
			ChangeState(new PlayerChangeLevelState(false,BIG));
		}
		else {
			EFFECT_SCORE_100
		}
		break;
	case GREEN_MUSHROOM:
	{
		infor->LifeEarn(1);
		if (e->nx != 0 || e->ny != 0) {
			auto ef = Effects::CreateEffect(LIFE_UP);
			grid->AddMovingObject(ef, x, y);
		}
	}
		break;
	case BUTTON:
		if (e->nx != 0) {
			if (isOnSky) {
				y += dy;
			}
			else {
				//vy = 0;
			}
		}
		if (e->ny == -1) {
			vy = 0;
			isJumpDone = true;
			isOnSky = false;
			e->obj->startTimeDead();
		}
		break;
	case FIRE_FLOWER:
		if (level != FIRE) {
			ChangeState(new PlayerChangeLevelState(false,FIRE));
		}
		else EFFECT_SCORE_100
		break;
	}
	e->obj->isDead = true;
	
}
void Mario::UpdateWithGround(LPCOLLISIONEVENT e)
{
	if (e->ny == 1) {
		vy = 0;
		isJumpDone = true;
	}
	if (e->ny == -1)
	{
		vy = 0;
		isOnSky = false;
		Allow[FALLING] = true;
		currentLocationY = y;
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
	case BLOCK_QUESTION: 
		if (e->nx != 0) {
			if (isOnSky) {
				y += dy;
			}
			else {
				vx = 0;
			}
		}
		if (e->ny == 1)
		{
			vy = 0;
			e->obj->startTimeDead();
			if (e->obj->child == COIN) {
				infor->MoneyEarn(1);
			};
		}
		if (e->ny == -1) {
			vy = 0;
		}
		break;
	case BLOCK_BREAKABLE:
		if (e->nx != 0) {
			if (isOnSky) {
				y += dy;
			}
			else {
				
			}
		}
		if (e->ny == 1)
		{
			vy = 0;
			e->obj->startTimeDead();
			infor->ScoreEarn(20);
		}
		if (e->ny == -1) {
			vy = 0;
		}
		break;
	
	case GROUND_LAND:
		if (e->nx != 0) {
			vx = 0;
		}
		break;
	case BLOCK_MOVE:
		if (e->ny == -1) {
			Allow[FALLING] = false;
			e->obj->isDead = true;
			e->obj->startTimeDead();
		}
	}
	
	if (dynamic_cast<Card*>(e->obj)) {
		e->obj->isDead = true;
		e->obj->canDel = true;
		Card* card = dynamic_cast<Card*>(e->obj);
		infor->AddCard(card->GetTypeCard());
		Alert* alert = new Alert(card->GetTypeCard(), card->x, card->y);
		alert->Init();
		grid->AddStaticObject(alert, card->x, card->y);
		auto ef = Effects::CreateEffect(EFFECT_CARD, card->GetTypeCard());
		grid->AddMovingObject(ef, card->x, card->y);
		ChangeState(new PlayerEndSceneState());
	}
}
void Mario::UpdateWithGate(LPCOLLISIONEVENT e)
{
	if (e->obj->type == PORTAL) {
		vx = 0;
		vy = 0;
		if (dynamic_cast<Portal*>(e->obj))
		{

			Portal* p = dynamic_cast<Portal*>(e->obj);
			infor->SetSceneId(p->GetSceneId());
			infor->SetCurSceneId(p->GetSceneId());
			IsTouchPort = true;
			x = e->obj->x;
			y = e->obj->y;
			
		}
	}
	else if (e->obj->type == SCENE_GATE) {
		if (e->nx != 0) {
			x += dx;
			vy = 0;
		}
		if (e->ny == -1) {
			y += dy;
			vy = 0;
		}
		if (dynamic_cast<SceneGate*>(e->obj))
		{
			
			SceneGate* p = dynamic_cast<SceneGate*>(e->obj);
			infor->SetGateId(p->GetGateId());
			moveToTrigger = p->GetWayIn();
			IsTouchTrigger = true;
		}
	}
	else {
		if (e->nx != 0) {
			x += dx;
		}
		if (e->ny != 0) {
			y += dy;
		}
		if (dynamic_cast<CheckPoint*>(e->obj))
		{
			vx = vy = 0;
			x = e->obj->x;
			y = e->obj->y;
			IsTouchPort = false;
		}
	}
	
		
	
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
#define MARIO_X_WHIP x - 27
void Mario::Render() {
	state->Render();
	if (untouchable)
	{
		alpha = alpha == 255 ? 125 : 255;
	}
	else alpha = 255;

	if (!isFreezeTime) {
		if (GetState() == WHIPPING_LEFT)
		{
			CurAnimation->Render(MARIO_X_WHIP, y, alpha);
		}
		else
		{
			CurAnimation->Render(x, y, alpha);
		}
	}
	//RenderBoundingBox();
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
	if (WorldMapScene != PLAYER_IN_WORLD_MAP)
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
			if (!isWavingTail && player->Allow[RACCON_WHIPING_FLY])
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
			/*if (!isOnSky && Allow[FLYING])
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
			}*/
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
				if (!isShooting && Allow[FIRING_FIRE] && countShoot < 2) {
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
		case DIK_LEFT:
		{
			if (IsTouchTrigger && moveToTrigger == -1)
			{
				IsChangeTrigger = true;
				IsTouchTrigger = false;
			}
			break;
		}
		case DIK_RIGHT:
		{
			if (IsTouchTrigger && moveToTrigger == 1)
			{
				IsChangeTrigger = true;
				IsTouchTrigger = false;
			}
			break;
		}
		case DIK_UP:
		{
			if (IsTouchTrigger && moveToTrigger == -2)
			{
				IsChangeTrigger = true;
				IsTouchTrigger = false;
			}
			break;
		}
		case DIK_DOWN:
		{
			if (IsTouchTrigger && moveToTrigger == 2)
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
			y -= 60;
			break;
		}
		case DIK_3:
		{
			y -= 60;
			SetLevel(RACCOON);
			ChangeState(new PlayerStandingState());
			break;
		}
		case DIK_4:
		{
			y -= 60;
			SetLevel(FIRE);
			ChangeState(new PlayerStandingState());
			break;
		}
		case DIK_V:
		{
			
			Alert* alert = new Alert(CARD_FLOWER, x, y);
			alert->Init();
			grid->AddStaticObject(alert, x, y);
			break;
		}
		case DIK_F1:
		{
			SetPosition(150, 900);
			break;
		}
		case DIK_F2:
		{
			SetPosition(1734, 816);
			break;
		}
		case DIK_F3:
		{
			SetPosition(2160, 1152);
			break;
		}
		case DIK_F4:
		{
			SetPosition(4128, 336);
			break;
		}
		case DIK_F5:
		{
			SetPosition(x, 240);
			camera->SetCamPos(5328, 0);
			break;
		}
		case DIK_5:
		{
			SetPosition(2976, 384);
			camera->SetCamPos(2592, 0);
			break;
		}
		case DIK_F6:
		{
			SetPosition(7056, 240);
			break;
		}
		case DIK_F7:
		{
			SetPosition(7248, 1104);
			break;
		}
		case DIK_F8:
		{
			player->ChangeState(new PlayerChangeLevelState(false));
			break;
		}
		case DIK_F9:
		{
			player->ChangeState(new PlayerChangeLevelState(false,RACCOON));
			break;
		}
		case DIK_F10:
		{
			player->ChangeState(new PlayerChangeLevelState(true));
			break;
		}
		case DIK_I:
		{
			immortal = immortal ? false : true;
			if (immortal) {
				DebugOut(L"immortal mode\n");
			}
			else {
				DebugOut(L"normal mode\n");
			}
		}
		break;
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
		else if (keyCode[DIK_F1])
		{
			SetPosition(48, 144);
		}
	}
}
void Mario::OnKeyUp(int key) {
	if (WorldMapScene != PLAYER_IN_WORLD_MAP)
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
			if (level == RACCOON && !isFlying) {
				Allow[RACCON_WHIPING_FLY] = true;
				 isWavingTail = false;
			}
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
		WorldMapScene = level;
	}
	else
	{
		ChangeState(new PlayerWorlMapState(0));
		WorldMapScene = PLAYER_IN_WORLD_MAP;
	}
	SetPosition(x, y);
	SetSpeed(0, 0);
	isFreezeTime = false;
}
