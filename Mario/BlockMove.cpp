#include "BlockMove.h"
#define BLOCK_WIDTH 144
#define BLOCK_HEIGHT 48
BlockMove::BlockMove() {
	tag = GROUND;
	type = BLOCK_MOVE;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	SetBBox(BLOCK_WIDTH, BLOCK_HEIGHT);
	vx = -0.1f;
	vy = 0;
}

BlockMove::~BlockMove() {};
void BlockMove::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	x += dx;
	y += dy;
	if (isDead) {
		vx = 0;
		vy += WORLD_GRAVITY/3 * dt;
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
	CurAnimation->Render(x, y);
	RenderBoundingBox();
}
