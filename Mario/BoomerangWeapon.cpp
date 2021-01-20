#include "BoomerangWeapon.h"
#include "Camera.h"
#include "Mario.h"
#define BOOMERANG_SPEED_X 0.6
#define BOOMERANG_SPEED_Y 0.3
#define BOOMERANG_GRAVITY 0.0006
#define BOOMERANG_ATBEGIN 40
#define BOOMERANG_ATLAST 10


BoomerangWeapon::BoomerangWeapon(float nx,float x, float y)
{
	this->tag = ENEMY;
	tagChange = WEAPON;
	this->type = BOOMERRANG_WEAPON;
	animation_set = animationsSets->Get(type);
	ChangeAnimation(WEAPON_SHOOT_RIGHT);
	SetBBox(UNIT_GAME, UNIT_GAME);
	startX = x;
	startY = y + BOOMERANG_ATLAST;
	SetPosition(x, y - BOOMERANG_ATBEGIN);
	weaponOwner = ENEMY;
	vx = BOOMERANG_SPEED_X * nx;
	vy = -BOOMERANG_SPEED_Y;
}
BoomerangWeapon::~BoomerangWeapon()
{

}
void BoomerangWeapon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + widthBBox;
	b = t + heightBBox;
}

void BoomerangWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vx -= BOOMERANG_GRAVITY * dt;
	vy += BOOMERANG_GRAVITY * dt;
		
	x += dx;
	y += dy;
	if (isDead) {
		canDel = true;
		player->countShoot = player->countShoot <= 0 ? 0 : player->countShoot - 1;
	}
	UpdatePosititon(dt);

}

void BoomerangWeapon::UpdatePosititon(DWORD dt)
{
	if (x < camera->cam_x || x > camera->cam_x + camera->GetWidth() || y > camera->cam_y + camera->GetHeight())
	{
		isDead = true;
	}
	if (y > startY) {
		vy = 0;
	}
	
}

//void BoomerangWeapon::Render()
//{
//	Weapon::Render();
//}
