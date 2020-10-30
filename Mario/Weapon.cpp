#include "Weapon.h"
Weapon::Weapon()
{
	tag = WEAPON;
	isDead = false;
}

void Weapon::Render()
{
	int alpha = 255;
	
	CurAnimation->Render(x, y, alpha);
	//RenderBoundingBox();
	
}