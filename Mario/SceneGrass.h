#include "GameObject.h"

class SceneGrass : public GameObject
{
	Animation* CurAnimation;
public:
	SceneGrass() {
		type = GROUND_LAND;
		tag = GROUND;
		SetBBox(UNIT_GAME-6, UNIT_GAME-6);
		CurAnimation = Animations::GetInstance()->Get(70000);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	}
	void Render() {
		CurAnimation->Render(x, y);
		RenderBoundingBox();
	}
};
