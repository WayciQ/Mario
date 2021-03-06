#pragma once
#include "Whip.h"
#include "Fire.h"
#include "BoomerangWeapon.h"
class Weapons
{
public:
	Weapons() {};
	~Weapons() {};
	static Weapon* CreateWeapon(TYPE type, float nx , float ny , float x , float y, TAG tag = PLAYER)
	{
		switch (type)
		{
		case BOOMERRANG_WEAPON:
			return new BoomerangWeapon(nx,x, y);
			break;
		case FIRE_FIRE:
			return new Fire(nx, ny, x, y, tag);
			break;
		case WHIP:
			return new Whip();
			break;
		
		default:
			return NULL;
			break;
		}
	}
};

