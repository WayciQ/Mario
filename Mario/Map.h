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
	

public:
	Map();
	~Map();
	
	void LoadResourses(LPCWSTR gameFile);
	RECT GetPositionMap(int x, int y);
	RECT GetPositionTitle(int title);
	void GetPositionCam(RECT cam,int& xs, int& ys, int& xe, int& ye);
	void Render();
	void Update(float dt);
	
	static Map* GetInstance();
};

