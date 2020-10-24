#pragma once
#include "Sprites.h"

/*
	Sprite animation
*/
class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef AnimationFrame* LPANIMATION_FRAME;

class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	vector<LPANIMATION_FRAME> frames;
public:
	int currentFrame;
	bool isLastFrame; // check last frame 
	Animation(int defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
};

typedef Animation* LPANIMATION;

class Animations
{
	static Animations* __instance;
	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	void Clear();
	LPANIMATION Get(int id);
	static Animations* GetInstance();
};

class AnimationSet {
	unordered_map<int, LPANIMATION> animations;
public:
	void Add(int aniId, STATENAME NameState);
	void Add(int aniId, STATEOBJECT type);
	LPANIMATION Get(STATENAME NameState);
	LPANIMATION Get(STATEOBJECT type);
};
typedef AnimationSet* LPANIMATION_SET;

class AnimationSets									// use unodered_map to store the ani follow statename, type, state object
{	
	static AnimationSets* __instance;
	unordered_map<int, LPANIMATION_SET> animation_sets;
public:
	void Add(TYPE type, LPANIMATION_SET ani);
	LPANIMATION_SET Get(TYPE type);
	void Clear();
	static AnimationSets* GetInstance();
};