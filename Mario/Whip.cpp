#include "Whip.h"
#include "Mario.h"
#include "EffectHit.h"
#include "Grid.h"
Whip::Whip()
{
	type = WHIP;
	SetBBox(9, 7);
	SetPosition(player->x, player->y);
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
	

	auto Effect = new EffectHit();
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
			coEvents.at(i)->startTimeDead();
			coEvents.at(i)->isFlip = true;
			coEvents.at(i)->vy = -0.2f;
			coEvents.at(i)->vx = 0;
			coEvents.at(i)->SetState(ENEMY_DIE_FLIP);
			grid->AddStaticObject(Effect, x, y);
			break;
		case GROUND:
			if (coEvents.at(i)->type == BLOCK_QUESTION || coEvents.at(i)->type == BLOCK_BREAKABLE)
			{
				coEvents.at(i)->isDead = true;
				canDel = true;
			}
			break;
		}
	}
}

void Whip::UpdatePosititon(DWORD dt)
{
	int curFrame = player->CurAnimation->currentFrame;
	int posX, posY;
	if (curFrame == 0)
	{
		posX = player->nx > 0 ? player->x  : player->x + 15;
	}
	else if (curFrame == 3)
	{
		posX = player->nx > 0 ? player->x + 25 : player->x - 9;
	}
	else posX = player->x + 15;
	posY = player->y + 18;
	SetPosition(posX, posY);
	if (player->CurAnimation->isLastFrame)	
		canDel = true;
}
void Whip::Render() {
	UpdatePosititon(dt);
	RenderBoundingBox();
}
Whip::~Whip(){}