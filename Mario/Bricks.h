#pragma once
#include "BrickBreakable.h"
#include "BrickCloud.h"
#include "BrickNormal.h"
#include "BrickQuestion.h"
#include "SwitchBlock.h"
class Bricks
{
public:
	Bricks() {};
	~Bricks() {};
	static Brick* CreateBrick(TYPE type, float CurY = NULL, TYPE child = MARIO)
	{
		switch (type)
		{
		case BLOCK_NORMAL:
			return new BrickNormal();
			break;
		case BLOCK_CLOUD:
			return new BrickCloud();
			break;
		case BLOCK_BREAKABLE:
			return new BrickBreakable();
			break;
		case BLOCK_QUESTION:
			return new BrickQuestion(CurY,child);
			break;
		/*case BUTTON:
			return new SwitchBlock();
			break;*/
		default:
			return NULL;
			break;
		}
	}
};