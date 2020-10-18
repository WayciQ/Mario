#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Utils.h"
#include "Textures.h"
#include <unordered_map>

using namespace std;

class Sprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	void Draw(float x, float y, float left, float top, float right, float bottom);
	void Draw(float x, float y, int alpha = 255);
};

typedef Sprite* LPSPRITE;

/*
	Manage sprite database
*/
class Sprites
{
	static Sprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	LPSPRITE& operator[](int id) { return sprites[id]; }
	void Clear();
	void LoadResources();
	static Sprites* GetInstance();
};