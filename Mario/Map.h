#pragma once
#include "GameGlobal.h"
#include "Sprites.h"
#include <fstream>

class Map
{
private:
	static Map* __instance;
	int col;			// col matrix
	int row;			// row matric
	int colTitle;		// col title
	int** mapTitles;	// arr store
	
	

public:
	D3DCOLOR backgroundcolor;
	float padding_left;
	float padding_top;
	Map();
	~Map();
	
	void LoadResourses(LPCWSTR gameFile);
	RECT GetPositionMap(int x, int y);	// get position element of the titleMap matrix
	RECT GetPositionTitle(int title);	// get RECT title need draw by value in titleMap maxtrix
	void GetPositionCam(int& xs, int& ys, int& xe, int& ye); // get position start cam, end cam with xs - x start, xe - x end, ys - y start, ye - y end
	void Render();
	void SetPadding(float left, float top) { 
		this->padding_left = left;
		this->padding_top = top;
	}
	void Update(float dt);
	float GetWidthMap();	// get width map
	float GetHeightMap();	// get height map
	static Map* GetInstance();
};

