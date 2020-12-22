#include "ParaGoomba.h"
#include "ParaKoomba.h"
#include "TropaKoompa.h"
#include "NipperPlant.h"
#include "PiranhaPlant.h"
#include "BasGoomba.h"
#include "BoomerangScene.h"
class Enemies
{
public:
	Enemies() {};
	~Enemies() {};
	static Enemy* CreateEnemy(TYPE type, float x = 0, float y = 0)
	{
		switch (type)
		{
		case PARA_KOOMPA:
			return new ParaKoompa();
			break;
		case TROPA_KOOMPA:
			return new TropaKoompa();
			break;
		case PARA_GOOMBA:
			return new ParaGoomba();
			break;
		case BASIC_GOOMBA:
			return new BasGoomba();
			break;
		case NIPPER_PLANT:
			return new NipperPlant(x,y);
			break;
		case PIRANHA_PLANT_RED:
			return new PiranhaPlant(type, x, y);
			break;
		case PIRANHA_PLANT:
			return new PiranhaPlant(type, x, y);
			break;
		case BOOMERANG:
			return new BoomerangScene();
			break;
		default:
			return NULL;
			break;
		}

	}
};