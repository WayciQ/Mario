#pragma once
#include "Sprites.h"
#include "GameObject.h"
#include "GameGlobal.h"

class CLevel {
	std::unordered_map<int, LPANIMATION> animations;
public:
	void Add(int aniId, STATENAME NameState);
	LPANIMATION Get(STATENAME NameState);
};
typedef CLevel* LPMARIOLEVEL;

class LevelMario
{
	static LevelMario* __instance;

	std::unordered_map<int, LPMARIOLEVEL> levelAnimations;
public:
	void Add(LEVEL level, LPMARIOLEVEL ani);
	LPMARIOLEVEL Get(LEVEL level);
	static LevelMario* GetInstance();

};

