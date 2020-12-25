#include "GameObject.h"
#include "Camera.h"
#define ANIMATION_EFFECTBIGBANG 539
class EffectBigBang : public GameObject
{
public:
	Animation* CurAnimation;
	EffectBigBang() {
		CurAnimation = Animations::GetInstance()->Get(ANIMATION_EFFECTBIGBANG);
	}
	~EffectBigBang() {}
	void Render()
	{
		CurAnimation->Render(x, y);
		if (CurAnimation->isLastFrame)
			isDead = true;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		/*if (x < camera->cam_x || x > camera->cam_x + camera->GetWidth() || y > camera->cam_y + camera->GetHeight())
		{
			isDead = true;
		}*/
		if (isDead)
			canDel = true;
	}
};