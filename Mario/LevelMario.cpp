#include "LevelMario.h"

void CLevel::Add(int aniId, STATENAME NameState)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	animations[NameState] = ani;
}
LPANIMATION CLevel::Get(STATENAME NameState)
{
	return animations[NameState];
}

LevelMario* LevelMario::__instance = NULL;
void LevelMario::Add(LEVEL level, LPMARIOLEVEL ani)
{
	levelAnimations[level] = ani;
}
LPMARIOLEVEL LevelMario::Get(LEVEL level) {
	return levelAnimations[level];
}
LevelMario* LevelMario::GetInstance() {
	if (__instance == NULL) __instance = new LevelMario();
	return __instance;	
}