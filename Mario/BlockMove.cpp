#include "BlockMove.h"
#include "camera.h"
#define BLOCK_WIDTH 144
#define BLOCK_HEIGHT 48
#define SPEED_MOVE 0.1f
#define GRAVITY WORLD_GRAVITY/3
#define TIME_FALL 50
BlockMove::BlockMove() {
	tag = GROUND;
	type = BLOCK_MOVE;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(BLOCK_STATIC);
	SetBBox(BLOCK_WIDTH, BLOCK_HEIGHT);
	
	vy = 0;
}

BlockMove::~BlockMove() {};
void BlockMove::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	GameObject::Update(dt);
	x += dx;
	y += dy;
	if (GetTickCount()- TimeDead > TIME_FALL) {
		if (isDead) {
			vx = 0;
			vy += GRAVITY * dt;
		}
	}
	if (x < camera->cam_x + SCREEN_WIDTH && !isDead) {
		vx = -SPEED_MOVE;
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
	//RenderBoundingBox();
}
