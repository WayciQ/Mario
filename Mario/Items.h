#include "Coin.h"
#include "Leaf.h"
#include "Mushroom.h"

class Items
{
public:
	Items() {};
	~Items() {};
	
	static Item* CreateItem(TYPE type,float x,float y)
	{
		switch (type)
		{
		case COIN:
			return new Coin(x,y);
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
		default:
			break;
		}
	}
};

