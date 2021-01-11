#include "BlockMove.h"
BlockMove::BlockMove(float w, float h) {
	tag = GROUND;
	type = GROUND_LAND;
	animation_set = animationsSets->Get(type);
	SetBBox(w, h);
	//vx = -0.2f;
	vy = 0;
}

BlockMove::~BlockMove() {};
void BlockMove::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	x += dx;
	y += dy;
	if (isDead) {
		vx = 0;
		vy += WORLD_GRAVITY * dt;
	}
}
void BlockMove::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}

void BlockMove::Render()
{
	RenderBoundingBox();
}