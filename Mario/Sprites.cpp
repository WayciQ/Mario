#include "Sprites.h"
#include "Game.h"

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
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}
void Sprite::Draw(float x, float y, float left, float top, float right, float bottom)
{
	game->Draw(x, y, texture, left, top, right, bottom, 255);
}
void Sprite::DrawFlip(float x, float y, D3DXVECTOR2& vtScale)
{
	game->DrawFlip(x, y, texture, vtScale, left, top, right, bottom, 255);
}
void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, left, top, right, bottom);
}

LPSPRITE Sprites::Get(int id)
{
	return sprites[id];
}



void Sprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}