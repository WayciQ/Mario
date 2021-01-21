#include "Coin.h"
#include "Leaf.h"
#include "Mushroom.h"
#include "SwitchBlock.h"
#include "FireFlower.h"
class Items
{
public:
	Items() {};
	~Items() {};
	
	static Item* CreateItem(TYPE type,float x,float y,bool isStatic = true, STATEOBJECT state = BLOCK_STATIC)
	{
		switch (type)
		{
		case COIN:
			return new Coin(x,y, state,isStatic);
			break;
		case RED_MUSHROOM:
			return new Mushroom(type,x,y);
			break;
		case GREEN_MUSHROOM:
			return new Mushroom(type,x,y);
			break;
		case LEAF:
			return new Leaf(x,y);
			break;
		case BUTTON:
			return new SwitchBlock(x,y);
			break;
		case FIRE_FLOWER:
			return new FireFlower(x, y);
			break;
		default:
			break;
		}
	}
};

