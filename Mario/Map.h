#pragma once
#include "GameGlobal.h"
#include "Sprites.h"
#include <fstream>
#define ID_TEXTURE_MAP_1 40


class Map
{
private:
	static Map* __instance;
	int col;
	int row;
	int** mapTiles;
public:
	Map();
	~Map();
	/*float cam_x = 0.0f;
	float cam_y = 0.0f;*/
	void LoadResourses();
	void Render();
	//void Update(float dt);
	//void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	static Map* GetInstance();
};

