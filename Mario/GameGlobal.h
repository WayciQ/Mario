#pragma once
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
#include <vector>
#include <iostream> 
#include <string> 
#include <unordered_set> 
#include <map>
#include "debug.h"

using namespace std;
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define TITLE_WIDTH 32
#define TITLE_HEIGHT 32
// mario
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_INERTIA 0.005f
#define MARIO_WALKING_SPEED		0.1f 
#define MARIO_WALKING_SPEED_PUSH 0.3f
#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.001f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_BIG_BOUNDING_BOX 111
#define MARIO_STATE_BIG_SIT_BOUNDING_BOX 100
#define MARIO_STATE_SMALL_BOUDING_BOX 222

#define MARIO_BIG_BBOX_WIDTH  22
#define MARIO_BIG_BBOX_HEIGHT 30

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_BIG_SIT_BBOX_WIDTH 23
#define MARIO_BIG_SIT_BBOX_HEIGHT 19

#define MARIO_RACCOON_FIGHT_WIDTH 22
#define MARIO_RACCOON_FIGHT_HEIGHT 30
#define MARIO_RACCOON_FIGHT_WIDTH_X 8

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_LAST_RUN_TIME 350

#define MARIO_RACCOON_WHIP_WIDTH 9
#define MARIO_RACCOON_WHIP_HEIGHT 5


extern enum STATENAME {
	STANDING,
	STANDING_LEFT,
	STANDING_RIGHT,
	WALKING,
	WALKING_LEFT,
	WALKING_RIGHT,
	JUMPING,
	JUMPING_LEFT,
	JUMPING_RIGHT,
	FALLING,
	FALLING_LEFT,
	FALLING_RIGHT,
	SITTING,
	SITTING_LEFT,
	SITTING_RIGHT,
	WHIPPING,
	WHIPPING_LEFT,
	WHIPPING_RIGHT,
	LAST_RIGHT,
	LAST_LEFT,
	
};extern enum LEVEL {
	SMALL,
	BIG,
	RACCOON,
	FIRE
};
extern enum TYPE {
	BRICK,
	WHIP,
	GOOMBA,
	GOOMBA_DIE
};
extern enum TAG
{
	PLAYER,
	ENEMY,
	WEAPON,
	ITEM,
	HOLDER,
	GROUND,
	EFFECT,
	BOX,
};

extern std::unordered_map<std::string, TYPE>   TYPEString;
extern std::unordered_map<std::string, STATENAME>   STATEString;
extern std::unordered_map<int, bool> keyCode; // manager info of keyboard have been pressed or not 
#define player Mario::GetInstance()
#define GAME  Game::GetInstance()
extern std::unordered_map<int, bool> Allow;
#define ADDITEM(x)  TYPEString.insert(std::pair<std::string,TYPE>(#x,x));
class GameGlobal
{
	/*void TypeMapToString()
	{
		ADDITEM(BRICK, "BRICK");
	}*/
};

