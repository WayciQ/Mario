#include "Map.h"
#include "Textures.h"
#include "Mario.h"
#include "Camera.h"
Map* Map::__instance = NULL;
Map::Map(){}

void Map::LoadResourses(LPCWSTR gameFile) {
	ifstream f;
	f.open(gameFile);
	f >> col >> row >> colTitle;
	mapTitles = new int* [row];

	// int **  to store title of matrix map
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

float Map::GetWidthMap() 
{
	return col * TITLE_WIDTH + TITLE_WIDTH;
}
float Map::GetHeightMap()
{
	return row * TITLE_HEIGHT + TITLE_HEIGHT;	
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
	t.left = j == 0 ?  TITLE_WIDTH * colTitle - TITLE_WIDTH: TITLE_WIDTH * j - TITLE_WIDTH; // if title % colTitle = 0 mean title is last colTitle else j = title % colTitle
	t.top = title > colTitle ? i * TITLE_HEIGHT : 0; // if title / colTitle = 1  mean title is last colTitle
	t.right = t.left + TITLE_WIDTH;
	t.bottom = t.top + TITLE_HEIGHT;
	return t;
	
}
void Map::GetPositionCam(int &xs, int& ys, int& xe, int& ye)
{
	RECT cam = Camera::GetInstance()->GetBound();

	int width = GetWidthMap();

	int left = (int)cam.left;
	int top = (int)cam.top;
	int bottom = (int)cam.bottom;
	int right = (int)cam.right;

	xs = left == 0 ? 0 : left / TITLE_WIDTH;
	ys = top < 16 ? 1 : top / TITLE_HEIGHT;
	ye = bottom / TITLE_HEIGHT + 1;
	xe = right == width ? col : right / TITLE_WIDTH - 1;
	//DebugOut(L"cam l:%d\n t:%d\n r:%d\n b:%d\n", xs, ys, xe, ye);
}

void Map::Render() {
	RECT r;
	RECT t;
	Sprite * sprite = Sprites::GetInstance()->Get(9991);

	int xs, ys, xe, ye;
	GetPositionCam( xs, ys, xe, ye);
	
	for (int i = ys; i <= ye; ++i)
	{
		for (int j = xs; j <= xe; ++j)
		{
			if (mapTitles[i][j] >= 0)
			{
				r = GetPositionMap(j, i);
				t = GetPositionTitle(mapTitles[i][j]);
				sprite->Draw(r.left, r.top, t.left, t.top, t.right, t.bottom);
			}
		}
	}
		
}
 
void Map::Update(float dt) {
}
Map* Map::GetInstance()
{
	if (__instance == NULL)
		__instance = new Map();
	return __instance;
}

Map::~Map() {
}