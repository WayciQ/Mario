#include "Weapon.h"
Weapon::Weapon()
{
	tag = WEAPON;
	isDead = false;
}

void Weapon::Render()
{
	CurAnimation->Render(x, y);
	//RenderBoundingBox();
}