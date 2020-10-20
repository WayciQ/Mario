#include "Map.h"
#include "Textures.h"
#include "Mario.h"
Map* Map::__instance = NULL;
Map::Map(){}

void Map::LoadResourses(LPCWSTR gameFile) {
	ifstream f;
	f.open(gameFile);
	f >> col >> row >> colTitle;
	mapTitles = new int* [row];
	for (int r = 0; r < row; ++r)
	{
		mapTitles[r] = new int[col];
		for (int c = 0; c < col; ++c)
		{
			f >> mapTitles[r][c];
			//DebugOut(L"[INFO] Map loaded OK: %d,[%d],[%d]\n", mapTitles[r][c],r,c);
		}
	}
	f.close();
	DebugOut(L"[INFO] Map loaded OK: %s\n", gameFile);

}
RECT Map::GetPositionMap(int x, int y)
{
	RECT r;
	r.left = x * TITLE_WIDTH;
	r.top = y * TITLE_HEIGHT;
	return r;
}
RECT Map::GetPositionTitle(int title)
{
	RECT t;
	title++;
	int i = title / colTitle;		// get top
	int j = title % colTitle;		// get left
	t.left = j == 0 ?  TITLE_WIDTH * colTitle - TITLE_WIDTH: TITLE_WIDTH * j - TITLE_WIDTH; // if title % colTitle = 0 mean title is 29th else j = title % colTitle
	t.top = title > colTitle ? i * TITLE_HEIGHT : 0; // if title / colTitle = 1  mean title is 29th
	t.right = t.left + TITLE_WIDTH;
	t.bottom = t.top + TITLE_HEIGHT;
	return t;
	
}
void Map::Render() {
	RECT r;
	RECT t;
	Sprite *  sprite = Sprites::GetInstance()->Get(9991);
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{ 
			if(mapTitles[i][j] != -1)
			{
				r = GetPositionMap(j, i);
				t = GetPositionTitle(mapTitles[i][j]);
				sprite->Draw(r.left, r.top, t.left, t.top, t.right, t.bottom);
			}
			
		}
	
}
 
void Map::Update(float dt) {
	float cx, cy;
	player->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	SetCamPos(cx,  cy);
}
Map* Map::GetInstance()
{
	if (__instance == NULL)
		__instance = new Map();
	return __instance;
}

Map::~Map() {
}