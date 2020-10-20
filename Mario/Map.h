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
	int colTitle;
	int** mapTitles;
	float cam_x = 0.0f;
	float cam_y = 0.0f;

public:
	Map();
	~Map();
	
	void LoadResourses(LPCWSTR gameFile);
	RECT GetPositionMap(int x, int y);
	RECT GetPositionTitle(int title);
	void Render();
	void Update(float dt);
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }
	static Map* GetInstance();
};

