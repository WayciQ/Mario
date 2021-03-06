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

#define GAME_DATA L"resource\\data\\mario-scene.txt"

#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2

#define SCREEN_WIDTH	786
#define SCREEN_HEIGHT	816

#define BACKGROUND_COLOR map->backgroundcolor
#define WINDOW_CLASS_NAME L"Mario"
#define MAIN_WINDOW_TITLE L"Mario"
#define MAX_FRAME_RATE 120

#define TITLE_WIDTH 48
#define TITLE_HEIGHT 48

#define ID_TEX_MARIO 1
#define ID_TEX_ENEMY 2
#define ID_TEX_BRICK 3
#define ID_TEX_FIRE 3
#define ID_TEXTURE_MAP_1 32

// mario
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_INERTIA_WALKING 0.02f
#define MARIO_WALKING_SPEED		0.3f 
#define MARIO_INERTIA_RUNNING 0.010f
#define MARIO_RUNNING_SPEED		0.5f
#define MARIO_JUMP_SPEED_Y		0.6f
#define MARIO_JUMP_DEFLECT_SPEED 0.6f
#define WORLD_GRAVITY			0.003f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_STATE_BIG_BOUNDING_BOX 111
#define MARIO_STATE_BIG_SIT_BOUNDING_BOX 100
#define MARIO_STATE_SMALL_BOUDING_BOX 222
#define MARIO_WORLDMAP_BOUDING_BOX 333


// bbx
#define MARIO_BIG_BBOX_WIDTH  45
#define MARIO_BIG_BBOX_HEIGHT 81

#define MARIO_SMALL_BBOX_WIDTH  39
#define MARIO_SMALL_BBOX_HEIGHT 48

#define MARIO_WORLDMAP_BBOX_WIDTH  42
#define MARIO_WORLDMAP_BBOX_HEIGHT 48

#define MARIO_BIG_SIT_BBOX_TOP 36
#define MARIO_BIG_SIT_BBOX_WIDTH 54
#define MARIO_BIG_SIT_BBOX_HEIGHT 42

#define MARIO_RACCOON_FIGHT_WIDTH 42
#define MARIO_RACCOON_FIGHT_HEIGHT 84
#define MARIO_RACCOON_FIGHT_WIDTH_X 27

#define MARIO_UNTOUCHABLE_TIME 3000
#define MARIO_LAST_RUN_TIME 300

#define MARIO_RACCOON_WHIP_WIDTH 27
#define MARIO_RACCOON_WHIP_HEIGHT 21

#define UNIT_GAME 48

extern enum STATEPLAYER {
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

	WAVING_TAIL,
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

	FLYING,
	FLYING_RIGHT,
	FLYING_LEFT,

	FLYING_FALL,
	FLYING_FALL_RIGHT,
	FLYING_FALL_LEFT,

	FLYING_PUSH,
	FLYING_PUSH_RIGHT,
	FLYING_PUSH_LEFT,

	RACCON_WHIPING_FLY,
	RACCON_WHIPING_FLY_RIGHT,
	RACCON_WHIPING_FLY_LEFT,

	JUMPING_SHORT,

	FIRING_FIRE,
	STANDING_FIRE_RIGHT,
	STANDING_FIRE_LEFT,

	JUMPING_FIRE,
	JUMPING_FIRE_RIGHT,
	JUMPING_FIRE_LEFT,

	KICKING,
	KICKING_RIGHT,
	KICKING_LEFT,

	PICKING,
	PICKING_RIGHT,
	PICKING_LEFT,

	DIE,
	STANDING_PICK_RIGHT,
	STANDING_PICK_LEFT,

	UP_SIZE_RIGHT,
	UP_SIZE_LEFT,
	DOWN_SIZE_RIGHT,
	DOWN_SIZE_LEFT,
	IDLE_WORLD_MAP,
	IDLE_CHANGE_GATE,
};

extern enum STATEOBJECT {
	BLOCK_STATIC,
	BLOCK_HITTED,
	WEAPON_SHOOT_RIGHT,
	WEAPON_SHOOT_LEFT,
	BIGBANG,
	ENEMY_WALKING_RIGHT,
	ENEMY_WALKING_LEFT,
	ENEMY_DIE_STAND,
	ENEMY_DIE_FLIP,
	ENEMY_JUMPING_RIGHT,
	ENEMY_JUMPING_LEFT,
	KOOMPA_KICKED,
	KOOMPA_KICKED_FLIP,
	KOOMPA_RESPAWN,
	KOOMPA_RESPAWN_FLIP,
	PLANT_UP,
	PLANT_SHOOT_UP_RIGHT,
	PLANT_SHOOT_DOWN_RIGHT,
	PLANT_SHOOT_UP_LEFT,
	PLANT_SHOOT_DOWN_LEFT,
	CARD_EMPTY,
	CARD_MUSHROOM,
	CARD_FLOWER,
	CARD_STAR,
	ENEMY_FLYING_RIGHT,
	ENEMY_FLYING_LEFT,
	ENEMY_SHOOTING_RIGHT,
	ENEMY_SHOOTING_LEFT
};
extern enum TYPE {
	MARIO,
	SMALL,
	BIG,
	RACCOON,
	FIRE,
	BLOCK,
	WHIP,
	GRASS,
	WEAPON_MARIO,
	GROUND_BOX,
	FIRE_FIRE,
	GROUND_LAND,
	BLOCK_QUESTION,
	BLOCK_BREAKABLE,
	BLOCK_NORMAL,
	BLOCK_CLOUD,
	KOOMPA,
	PARA_KOOMPA,
	TROPA_KOOMPA,
	GOOMBA,
	BASIC_GOOMBA,
	PARA_GOOMBA,
	NIPPER_PLANT,
	PIRANHA_PLANT_RED,
	PIRANHA_PLANT,
	PLANT,
	COIN,
	RED_MUSHROOM,
	GREEN_MUSHROOM,
	LEAF,
	BUTTON,
	EFFECT_BIGBANG,
	EFFECT_STAR,
	SCENE_GATE,
	PORTAL,
	CHECKPOINT,
	PLAYER_IN_WORLD_MAP,
	CARD,
	CARD_HUB,
	BOOMERANG_SCENE,
	NUMBER_SCENE,
	BLOCK_MOVE,
	BOOMERRANG_ENEMY,
	BOOMERRANG_WEAPON,
	FIRE_FLOWER,
	CURTAIN,
	SCORE_100,
	LIFE_UP,
	EFFECT_CARD,
	BRICKBREAK_10_TIME,
};
extern enum TAG
{
	PLAYER,
	ENEMY,
	WEAPON,
	ITEM,
	GROUND,
	BOX,
	EFFECT,
};


extern unordered_map<int, bool> keyCode; // manager info of keyboard have been pressed or not 
#define player Mario::GetInstance()
#define game  Game::GetInstance()
#define camera Camera::GetInstance()
#define animationsSets AnimationSets::GetInstance()
#define grid Grid::GetInstance()
#define scoreBoard HUB::GetInstance()
#define map Map::GetInstance()

class GameGlobal
{
	
};

