#include "Whip.h"
#include "Mario.h"
Whip::Whip()
{
	type = WHIP;
	SetBBox(30, 7);

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
	

	UpdatePosititon(dt);
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
			break;
		case GROUND:
			if (coEvents.at(i)->type == BRICK_QUESTION)
			{
				coEvents.at(i)->isDead = true;
			}
			break;
		}
	}
}

void Whip::UpdatePosititon(DWORD dt)
{
	int posX = player->nx > 0 ? player->x : player->x - 7;
	int	posY = player->nx > 0 ? player->y + 15 : player->y +15;

	SetPosition(posX, posY);
	if (player->CurAnimation->isLastFrame)	
		canDel = true;
}
void Whip::Render() {
	RenderBoundingBox();
}
Whip::~Whip(){}