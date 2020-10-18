#include "Animations.h"


void Animation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) {
				currentFrame = 0;
				isLastFrame = true;
			}
		}
		else
		{
			isLastFrame = false;
			t += now - lastFrameTime;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

Animations* Animations::__instance = NULL;

Animations* Animations::GetInstance()
{
	if (__instance == NULL) __instance = new Animations();
	return __instance;
}

void Animations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}
void Animations::LoadResources() {
	ifstream File;
	File.open(L"resource\\animations.txt");
	vector<int> ParaAni;
	ParaAni.clear();
	vector<int>::iterator it;
	int reader;
	int time;
	while (!File.eof())
	{
		File >> reader;
		if (reader > -1)
		{
			ParaAni.push_back(reader);
		}
		else
		{
			LPANIMATION ani;
			if (reader < -1)
				ani = new Animation(abs(reader));
			else
				ani = new Animation(100);
			for (auto it = ParaAni.begin(); it != ParaAni.end() - 1; ++it)
				ani->Add(*it);
			it = ParaAni.end() - 1;
			Add(*it, ani);
			ParaAni.clear();
		}
		DebugOut(L"[INFO] Animations loaded Ok: id=%d, %d \n", it);
	}
	File.close();

}

LPANIMATION Animations::Get(int id)
{
	LPANIMATION ani = animations[id];
	if (ani == NULL)
		DebugOut(L"[ERROR] Failed to find animation id: %d\n", id);
	return ani;
}

void Animations::Clear()
{
	for (auto x : animations)
	{
		LPANIMATION ani = x.second;
		delete ani;
	}

	animations.clear();
}


void AnimationSet::Add(int aniId, STATENAME NameState)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	animations[NameState] = ani;
}
void AnimationSet::Add(int aniId, STATEOBJECT type)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	animations[type] = ani;
}
LPANIMATION AnimationSet::Get(STATENAME NameState)
{
	return animations[NameState];
}
LPANIMATION AnimationSet::Get(STATEOBJECT type)
{
	return animations[type];
}

AnimationSets* AnimationSets::__instance = NULL;

void AnimationSets::Add(TYPE type, LPANIMATION_SET ani)
{
	animation_sets[type] = ani;
}

LPANIMATION_SET AnimationSets::Get(TYPE type) {
	return animation_sets[type];
}

AnimationSets* AnimationSets::GetInstance() {
	if (__instance == NULL) __instance = new AnimationSets();
	return __instance;
}