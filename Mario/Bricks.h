#pragma once
#include "BrickBreakable.h"
#include "BrickCloud.h"
#include "BrickNormal.h"
#include "BrickQuestion.h"

class Bricks
{
public:
	Bricks() {};
	~Bricks() {};
	static Brick* CreateBrick(TYPE type, float CurY = NULL)
	{
		switch (type)
		{
		case BRICK_NORMAL:
			return new BrickNormal();
			break;
		case BRICK_CLOUD:
			return new BrickCloud();
			break;
		case BRICK_BREAKABLE:
			return new BrickBreakable();
			break;
		case BRICK_QUESTION:
			return new BrickQuestion(CurY);
			break;
		default:
			return NULL;
			break;
		}
	}
};