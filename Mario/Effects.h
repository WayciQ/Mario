#include "Number.h"
#include "Effectbigbang.h"
#include "EffectStar.h"
#include "Curtain.h"
class Effects
{
public:
	Effects() {};
	~Effects() {};
	static Effect* CreateEffect(TYPE type) {
		switch (type)
		{
		case NUMBER_SCENE:
			return new Number();
			break;
		case EFFECT_BIGBANG:
			return new EffectBigBang();
			break;
		case EFFECT_STAR:
			return new EffectStar();
			break;
		case CURTAIN:
			return new Curtain();
			break;
		default:
			break;
		}
	}

};
