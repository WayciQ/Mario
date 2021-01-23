#include "Whip.h"
#include "Mario.h"
#include "Effects.h"
#include "Grid.h"
Whip::Whip()
{
	type = WHIP;
	isDead = false;
	SetBBox(MARIO_RACCOON_WHIP_WIDTH, MARIO_RACCOON_WHIP_HEIGHT);
	//SetPosition(player->x, player->y);
}

void Whip::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	vector<LPGAMEOBJECT> coEventsCreate;
	coEventsCreate.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (IsCollisionAABB(GetRect(), coObjects->at(i)->GetRect()))
		{
			coEventsCreate.push_back(coObjects->at(i));
		}
	}
	
	for (UINT i = 0; i < coEventsCreate.size(); i++)
	{
		switch(coEventsCreate.at(i)->tag)
		{
		case ENEMY:
		{
			auto effect = Effects::CreateEffect(EFFECT_STAR);
			grid->AddStaticObject(effect, x, y);
			auto ef = Effects::CreateEffect(SCORE_100);
			grid->AddStaticObject(ef, x, y);
			canDel = true;
			coEventsCreate.at(i)->vx = 0;
			coEventsCreate.at(i)->startTimeDead();
			coEventsCreate.at(i)->isFlip = true;
			coEventsCreate.at(i)->vy = -MARIO_JUMP_DEFLECT_SPEED;
			coEventsCreate.at(i)->SetState(ENEMY_DIE_FLIP);
			
		}
			break;
		case GROUND:
			if (coEventsCreate.at(i)->type == BLOCK_QUESTION || coEventsCreate.at(i)->type == BLOCK_BREAKABLE)
			{
				canDel = true;
				coEventsCreate.at(i)->startTimeDead();
			}
			break;
		}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() != 0) {
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			switch (e->obj->tag)
			{
			case ENEMY:
			{
				auto effect = Effects::CreateEffect(EFFECT_STAR);
				grid->AddStaticObject(effect, x, y);
				auto ef = Effects::CreateEffect(SCORE_100);
				grid->AddStaticObject(ef, x, y);
				canDel = true;
				e->obj->vx = 0;
				e->obj->startTimeDead();
				e->obj->isFlip = true;
				e->obj->vy = -MARIO_JUMP_DEFLECT_SPEED;
				e->obj->SetState(ENEMY_DIE_FLIP);

			}
			break;
			case GROUND:
				if (e->obj->type == BLOCK_QUESTION || e->obj->type == BLOCK_BREAKABLE)
				{
					canDel = true;
					e->obj->startTimeDead();
				}
				break;
			}
		}
	}
}
#define X_TAIL_1_FRAME_3 player->x + 76
#define X_TAIL_2_FRAME_3 player->x - 27
#define X_TAIL_1_FRAME_0 player->x
#define X_TAIL_2_FRAME_0 player->x + 45
#define X_TAIL_2_FRAME player->x + 24
#define Y_TAIL_2_FRAME player->y + 54

void Whip::UpdatePosititon(DWORD dt)
{
	int curFrame = player->CurAnimation->currentFrame;
	
	int posX, posY;
	if (curFrame == 0) {
		SetBBox(0, 0);
		posX = player->nx > 0 ? X_TAIL_1_FRAME_0 : X_TAIL_2_FRAME_0;
	}
	else
	if (curFrame == 3)
	{
		SetBBox(MARIO_RACCOON_WHIP_WIDTH, MARIO_RACCOON_WHIP_HEIGHT);
		posX = player->nx > 0 ? X_TAIL_1_FRAME_3 : X_TAIL_2_FRAME_3;
	}
	else {
		posX = player->nx > 0 ? X_TAIL_1_FRAME_3 : X_TAIL_2_FRAME_3;
		SetBBox(MARIO_RACCOON_WHIP_WIDTH, MARIO_RACCOON_WHIP_HEIGHT);
	}

	posY = Y_TAIL_2_FRAME;
	SetPosition(posX, posY);

	if (player->CurAnimation->isLastFrame)
	{
		canDel = true;
		isDead = true;
	}

}
void Whip::Render() {
	UpdatePosititon(dt);
	//RenderBoundingBox();
}
Whip::~Whip(){}