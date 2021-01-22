#include "Number.h"
#include "Effectbigbang.h"
#include "EffectStar.h"
#include "Curtain.h"
#include "Score_100.h"
#include "LifeUp.h"
#include "CardSelect.h"

class Effects
{
public:
	Effects() {};
	~Effects() {};
	static Effect* CreateEffect(TYPE type, STATEOBJECT card = BLOCK_STATIC) {
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
		case SCORE_100:
			return new Score_100();
			break;
		case LIFE_UP:
			return new LifeUp();
			break;
		case EFFECT_CARD:
			return new CardSelect(card);
			break;
		default:
			break;
		}
	}

};
