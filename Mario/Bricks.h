#pragma once
#include "BrickBreakable.h"
#include "BrickCloud.h"
#include "BrickNormal.h"
#include "BrickQuestion.h"
#include "Card.h"
class Bricks
{
public:
	Bricks() {};
	~Bricks() {};
	static Brick* CreateBrick(TYPE type, float CurY = NULL, TYPE child = MARIO, int NumHit = 1)
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
			return new BrickBreakable(CurY,child, NumHit);
			break;
		case BLOCK_QUESTION:
			return new BrickQuestion(CurY,child);
			break;
		case CARD:
			return new Card();
			break;
		default:
			return NULL;
			break;
		}
	}
};