#include "Number.h"

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
		}
	}

};
