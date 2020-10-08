#include "Sprites.h"
#include "Game.h"
#include "debug.h"

Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

Sprites* Sprites::__instance = NULL;

Sprites* Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}

void Sprite::Draw(float x, float y, int alpha)
{
	Game* game = Game::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}
void Sprite::Draw(float x, float y, float left, float top, float right, float bottom)
{
	Game* game = Game::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, 245);
}
void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE Sprites::Get(int id)
{
	return sprites[id];
}



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
void Sprites::LoadResources(){
	ifstream File;
	File.open(L"resource\\sprites.txt");
	int idSpirtes, left, top, right, bottom, Idtex;
	Textures* textures = Textures::GetInstance();
	while (!File.eof())
	{

		File >> idSpirtes >> left >> top >> right >> bottom >> Idtex;
		LPDIRECT3DTEXTURE9 textWhip = textures->Get(Idtex);
		Add(idSpirtes, left, top, right, bottom, textWhip);
		DebugOut(L"[INFO] Sprites loaded Ok: id=%d, %d \n", idSpirtes, textWhip);
	}
	File.close();
}
LPANIMATION Animations::Get(int id)
{
	return animations[id];
}