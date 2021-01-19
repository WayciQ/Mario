#include "ParaGoomba.h"
#include "ParaKoomba.h"
#include "TropaKoompa.h"
#include "NipperPlant.h"
#include "PiranhaPlant.h"
#include "BasGoomba.h"
#include "BoomerangScene.h"
#include "BoomerangEnemy.h"
class Enemies
{
public:
	Enemies() {};
	~Enemies() {};
	static Enemy* CreateEnemy(TYPE type, float x = 0, float y = 0, STATEOBJECT state = ENEMY_WALKING_LEFT)
	{
		switch (type)
		{
		case PARA_KOOMPA:
			return new ParaKoompa(state);
			break;
		case TROPA_KOOMPA:
			return new TropaKoompa(state);
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
		case BOOMERRANG_ENEMY:
			return new BoomerangEnemy();
			break;
		case BOOMERANG_SCENE:
			return new BoomerangScene();
			break;
		
		default:
			return NULL;
			break;
		}

	}
};