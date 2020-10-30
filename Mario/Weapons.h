#pragma once
#include "Whip.h"
#include "Fire.h"
class Weapons
{
public:
	Weapons() {};
	~Weapons() {};
	static Weapon* CreateWeapon(TYPE type)
	{
		switch (type)
		{
		case FIRE_FIRE:
			return new Fire();
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

