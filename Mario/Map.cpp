#include "Map.h"
#include "Textures.h"
#include "Mario.h"
#include "Camera.h"
Map* Map::__instance = NULL;
Map::Map(){}
#define ID_TEX_MAP 5
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
	int i = title / colTitle;		// get row
	int j = title % colTitle;		// get col
	t.left =TITLE_WIDTH * j;		// 
	t.top = title > colTitle-1 ? i * TITLE_HEIGHT : 0; // if title / colTitle = 1  mean title is last colTitle
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

	/*xs = left == 0 ? 0 : left / TITLE_WIDTH;
	ys = top < 16 ? 1 : top / TITLE_HEIGHT;
	ye = bottom / TITLE_HEIGHT - 5;
	xe = right == width ? col : right / TITLE_WIDTH - 1;*/
	xs = int(max(0, left / TITLE_WIDTH));
	ys = int(max(0, top / TITLE_HEIGHT));
	ye = int(min(row - 1, int(bottom / TITLE_HEIGHT)));
	xe = int(min(col - 1, int(right / TITLE_WIDTH)));
	//DebugOut(L"cam l:%d\n t:%d\n r:%d\n b:%d\n", xs, ys, xe, ye);
}

void Map::Render() {
	RECT r;
	RECT t;
	LPDIRECT3DTEXTURE9 Map = Textures::GetInstance()->Get(ID_TEX_MAP);
	
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
				
				Game::GetInstance()->Draw(r.left, r.top, Map, t.left, t.top, t.right, t.bottom,255);
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