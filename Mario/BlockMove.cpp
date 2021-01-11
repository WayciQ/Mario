#include "BlockMove.h"
BlockMove::BlockMove(float w, float h) {
	tag = GROUND;
	type = GROUND_LAND;
	SetBBox(w, h);
	vx = -MARIO_JUMP_DEFLECT_SPEED;
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