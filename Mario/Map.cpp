#include "Map.h"
#include "Textures.h"
#include "Mario.h"
Map* Map::__instance = NULL;
Map::Map(){}

void Map::LoadResourses() {
	ifstream File;
	char gridFileName[30];
	sprintf_s(gridFileName, "textures\\Level1.txt");
	File.open(gridFileName);
	File >> col >> row;
	mapTiles = new int* [row];
	for (int r = 0; r < row; r++) {
		mapTiles[r] = new int[col];
		for (int c = 0; c < col; c++) {
			File >> mapTiles[r][c];
		}
	}
	File.close();
}
void Map::Render() {
	Textures* tex = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texMap = tex->Get(ID_TEXTURE_MAP_1);
	Sprites* sprites = Sprites::GetInstance();

	sprites->Add(9991, 0, 0, 32, 1568, texMap);
	Sprite *  sprite = sprites->Get(9991);
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			RECT r;
			r.left = j * TITLE_WIDTH;
			r.top = i * TITLE_HEIGHT;
			r.right = r.left + TITLE_WIDTH;
			r.bottom = r.top + TITLE_HEIGHT;
				sprite->Draw(r.left, r.top, TITLE_WIDTH * mapTiles[i][j] - TITLE_WIDTH, 0, TITLE_HEIGHT * mapTiles[i][j], TITLE_HEIGHT);
		}
		
}
 
//void Map::Update(float dt) {
//	SetCamPos(player->x - SCREEN_WIDTH / 2, player->y - SCREEN_HEIGHT / 2);
//}
Map* Map::GetInstance()
{
	if (__instance == NULL)
		__instance = new Map();
	return __instance;
}

Map::~Map() {
}