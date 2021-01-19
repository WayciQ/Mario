#include "BoomerangWeapon.h"
BoomerangWeapon::BoomerangWeapon(float x, float y)
{
	this->tag = WEAPON;
	this->type = BOOMERRANG_WEAPON;
	animation_set = animationsSets->Get(type);
	SetBBox(UNIT_GAME, UNIT_GAME);
	startX = x;
	startY = y;
}
BoomerangWeapon::~BoomerangWeapon()
{
}
void BoomerangWeapon::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDead) {
		SetBBox(0,0);
	}
	l = x;
	t = y;
	r = l + widthBBox;
	b = t + heightBBox;
	
}

void BoomerangWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

}

void BoomerangWeapon::UpdatePosititon(DWORD dt)
{
}
