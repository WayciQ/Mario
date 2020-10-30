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
	vy += MARIO_GRAVITY * dt;
	GameObject::Update(dt);

	UpdatePosititon(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->tag == ENEMY)
			{
				e->obj->isDead = true;
			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Whip::UpdatePosititon(DWORD dt)
{
	int posX = player->nx > 0 ? player->x : player->x;
	int	posY = player->nx > 0 ? player->y + 15 : player->y +15;

	SetPosition(posX, posY);
	if (player->CurAnimation->isLastFrame)
		isDead = true;
}
void Whip::Render() {
	//RenderBoundingBox();
}
Whip::~Whip(){}