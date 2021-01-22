#include "GameObject.h"
#define ANIMATION 70000
#define WIDTH_BBOX UNIT_GAME-6
#define HEIGHT_BBOX  UNIT_GAME-6

class SceneGrass : public GameObject
{
	Animation* CurAnimation;
public:
	SceneGrass() {
		type = GROUND_LAND;
		tag = GROUND;
		SetBBox(UNIT_GAME-6, UNIT_GAME-6);
		CurAnimation = Animations::GetInstance()->Get(ANIMATION);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom) {
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	}
	void Render() {
		CurAnimation->Render(x, y);
		//RenderBoundingBox();
	}
};
