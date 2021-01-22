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
	
	vector<LPGAMEOBJECT> coEvents;
	coEvents.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (IsCollisionAABB(GetRect(), coObjects->at(i)->GetRect()))
		{
			coEvents.push_back(coObjects->at(i));
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		switch(coEvents.at(i)->tag)
		{
		case ENEMY:
		{
			auto effect = Effects::CreateEffect(EFFECT_STAR);
			grid->AddStaticObject(effect, x, y);
			auto ef = Effects::CreateEffect(SCORE_100);
			grid->AddStaticObject(ef, x, y);
			canDel = true;
			coEvents.at(i)->vx = 0;
			coEvents.at(i)->startTimeDead();
			coEvents.at(i)->isFlip = true;
			coEvents.at(i)->vy = -MARIO_JUMP_DEFLECT_SPEED;
			coEvents.at(i)->SetState(ENEMY_DIE_FLIP);
			
		}
			break;
		case GROUND:
			if (coEvents.at(i)->type == BLOCK_QUESTION || coEvents.at(i)->type == BLOCK_BREAKABLE)
			{
				canDel = true;
				coEvents.at(i)->startTimeDead();
			}
			break;
		}
	}
	if (isDead) {
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
	RenderBoundingBox();
}
Whip::~Whip(){}