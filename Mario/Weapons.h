#pragma once
#include "Whip.h"
#include "Fire.h"
class Weapons
{
public:
	Weapons() {};
	~Weapons() {};
	static Weapon* CreateWeapon(TYPE type,TAG tag = PLAYER, float nx = player->nx, float ny = player->ny, float x = player->x, float y = player->y)
	{
		switch (type)
		{
		case FIRE_FIRE:
			return new Fire(nx,ny, x, y,tag);
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

