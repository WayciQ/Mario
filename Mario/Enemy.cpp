#include "Enemy.h"
void Enemy::Render()
{
	CurAnimation->Render(x, y, 255);
	RenderBoundingBox();
}
//void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	GameObject::Update(dt, coObjects);
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;	
//	// turn off collision when die 
//	CalcPotentialCollisions(coObjects, coEvents);
//
//	// reset untouchable timer if untouchable time has passed
//	// No collision occured, proceed normally
//
//	if (coEvents.size() == 0)
//	{
//		x += dx;
//		y += dy;
//	}
//	else
//	{
//		// block 
//		float min_tx, min_ty, nx = 0, ny;
//
//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
//		
//		for (UINT i = 0; i < coEventsResult.size(); i++)
//		{
//			LPCOLLISIONEVENT e = coEventsResult[i];
//			auto object = e->obj;
//			if (object->tag == GROUND)
//			{
//				if (ny == 1 || nx != 0)
//				{
//					y += dy;
//					x += dx;
//				}
//				else
//				{
//					x += min_tx * dx + nx * 0.2f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
//					y += min_ty * dy + ny * 0.2f;
//					//IsJumping = false;
//				}
//			
//				if (ny == -1) vy = 0;
//				
//				IsEndGround = false;
//				if ((object->x + 4 > x) || ((object->x+ object->width) - 4 < x ) )
//				{
//					IsEndGround = true;
//				}
//			}
//		}
//		
//
//	}
//	// clean up collision events
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
//}