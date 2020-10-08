#include "Whip.h"
#include "Mario.h"
Whip* Whip::__instance = NULL;
Whip::Whip() {
	tag = WEAPON;
}
void Whip::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	if (player->GetState() == WHIPPING_RIGHT || player->GetState() == WHIPPING_LEFT) {
		right = left + MARIO_RACCOON_WHIP_WIDTH;
		bottom = top + MARIO_RACCOON_WHIP_HEIGHT;
	}
}
void Whip::Render() {
	RenderBoundingBox();
}
//void Whip::UpdatePosition(DWORD dt) {
//	if (player->level == MARIO_LEVEL_RACCOON)
//	{
//		int posX = player->nx > 0 ? player->x - 22 : player->x - 80;
//		int	posY = player->nx > 0 ? player->y + 1 : player->y;
//		SetPosition(posX, posY);
//	}
//}
void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
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
			//if (dynamic_cast<Goomba*>(e->obj)) // if e->obj is Goomba 
			//{
			//	Goomba* goomba = dynamic_cast<Goomba*>(e->obj);

			//	if (e->nx != 0 && nx != 0) {
			//		if (goomba->GetState() != GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			//DebugOut(L"cham nef: %d \n", e->nx);
			//		}
			//	}
			//}
		}
	}
}
Whip* Whip::GetInstance() {
	if (__instance == NULL) {
		__instance = new Whip();
	return __instance;
	}
}