#pragma once
#include <dinput.h>
#include <WinUser.h>
#include <unordered_map>
#include <vector>
#include <iostream> 
#include <string> 
#include <unordered_set> 
#include <map>
#include "Utils.h"

using namespace std;
#define MAX_GAME_LINE 1024

#define LOAD_DATA L"resource\\data\\mario-sample.txt"

#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 280

#define BACKGROUND_COLOR D3DCOLOR_XRGB(100, 255, 255)
#define WINDOW_CLASS_NAME L"Mario"
#define MAIN_WINDOW_TITLE L"Mario"
#define MAX_FRAME_RATE 120

#define TITLE_WIDTH 16
#define TITLE_HEIGHT 16

#define ID_TEX_MARIO 1

#define ID_TEX_ENEMY 11
#define ID_TEX_MISC 22
#define ID_TEX_FIRE 33
// mario
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_INERTIA_WALKING 0.005f
#define MARIO_WALKING_SPEED		0.1f 
#define MARIO_INERTIA_RUNNING 0.004f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.001f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_BIG_BOUNDING_BOX 111
#define MARIO_STATE_BIG_SIT_BOUNDING_BOX 100
#define MARIO_STATE_SMALL_BOUDING_BOX 222

#define MARIO_BIG_BBOX_WIDTH  22
#define MARIO_BIG_BBOX_HEIGHT 28

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 16

#define MARIO_BIG_SIT_BBOX_WIDTH 23
#define MARIO_BIG_SIT_BBOX_HEIGHT 19

#define MARIO_RACCOON_FIGHT_WIDTH 22
#define MARIO_RACCOON_FIGHT_HEIGHT 28
#define MARIO_RACCOON_FIGHT_WIDTH_X 8

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_LAST_RUN_TIME 350

#define MARIO_RACCOON_WHIP_WIDTH 9
#define MARIO_RACCOON_WHIP_HEIGHT 5


extern enum STATENAME {
	STANDING,
	STANDING_RIGHT,
	STANDING_LEFT,
	WALKING,
	WALKING_RIGHT,
	WALKING_LEFT,
	WALKING_FAST_RIGHT,
	WALKING_FAST_LEFT,
	RUNNING,
	RUNNING_RIGHT,
	RUNNING_LEFT,
	JUMPING,
	JUMPING_RIGHT,
	JUMPING_LEFT, 
	JUMP_SIT_RIGHT,
	JUMP_SIT_LEFT,
	FALLING,
	FALLING_RIGHT,
	FALLING_LEFT,
	SITTING,
	SITTING_RIGHT,
	SITTING_LEFT,
	WHIPPING,
	WHIPPING_RIGHT,
	WHIPPING_LEFT,
	LAST_RIGHT,
	LAST_LEFT,
	
};

extern enum STATEOBJECT {
	BRICK_NORMAL,
	BRICK_GROUND_HEAD,
	BRICK_GROUND_MID,
	BRICK_GROUND_END,
	GOOMBA_WALKING,
	GOOMBA_DIE,
};
extern enum TYPE {
	MARIO,
	SMALL,
	BIG,
	RACCOON, 
	FIRE,
	BRICK,
	GOOMBA,
	WHIP,
	
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

