#include "ScoreBoard.h"
#include "Mario.h"
#include "Camera.h"
#define HEIGHT_SCORE_BROAD 28
#define ID_TEX_HUB 7
#define POS_X camera->cam_x
#define POS_Y camera->cam_y + 192
#define POS_I1 POS_X + 160
#define POS_I2 POS_X + 183
#define POS_I3 POS_X + 206
#define POS_X_TP POS_X + 4
#define POS_Y_TP POS_Y + 16
#define POS_Y_TEX1 POS_Y + 6
#define POS_Y_TEX2 POS_Y + 15
ScoreBoard* ScoreBoard::__instance = NULL;
ScoreBoard::ScoreBoard() {
	isDrawPush = true;
}
void ScoreBoard::Init()
{
	
	font = NULL;
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 buffer = Game::GetInstance()->GetBackBuffer();
	AddFontResourceEx(L"resource\\font\\Super-Mario-Bros--3.ttf", FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		d3ddv,		// d3d divice
		9,			//	Height
		0,			//	Width
		FW_NORMAL,	//	Weight
		1,			//MipLevels
		false,		//Italic,
		DEFAULT_CHARSET, //CharSet
		OUT_CHARACTER_PRECIS, //OutputPrecision
		ANTIALIASED_QUALITY, // Quality
		FF_DONTCARE, // PitchAndFamily,
		L"Super Mario Bros. 3", 
		&font);

	SetRect(&rect, POS_X + 39, POS_Y_TEX1, POS_X + SCREEN_WIDTH, POS_Y + 30);
	information = "4                              01\n";
	information +="4   1241241       121\n";
	auto sprites = Sprites::GetInstance();
	HUB = sprites->Get(90000);
	Item1 = sprites->Get(90002);
	Item2 = sprites->Get(90003);
	Item3 = sprites->Get(90004);
	typePlayer = sprites->Get(92001);
	speed = sprites->Get(91001);
	push = sprites->Get(91002);
}
void ScoreBoard::Update(float dt)
{
	string scoregame = to_string(player->score);
	while (scoregame.length() < 7)
		scoregame = "0" + scoregame;
	string timeString = to_string(player->playTime);
	while (timeString.length() < 3)
		timeString = "0" + timeString;

	string life = to_string(player->life);

	string money = to_string(player->money);
	while (money.length() < 2)
		money = "  " + money;

	string scene = to_string(game->GetNumCurrentScene());

	float vx,vy;
		player->GetSpeed(vx,vy);
		NumSpeed = NumSpeed > 6 ? 6 : int(vx / 0.03);

	information = scene + "                              " + money + "\n";
	information += life +"   "+ scoregame +"     "+ timeString +"\n";
	
}
void ScoreBoard::Render()
{
	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_HUB);
	Game::GetInstance()->Draw(POS_X, POS_Y, bbox, 0, 0, camera->GetWidth(), 48, 255);
	
	
	HUB->Draw(POS_X, POS_Y);
	Item1->Draw(POS_I1, POS_Y);
	Item2->Draw(POS_I2, POS_Y);
	Item3->Draw(POS_I3, POS_Y);
	typePlayer->Draw(POS_X + 4, POS_Y + 15);
	for(int i = 0; i < NumSpeed; i++)
	{
		speed->Draw(POS_X + 53 + (i*8), POS_Y + 7);
	}
	isDrawPush = isDrawPush ? false : true;
	if (NumSpeed >= 6 && isDrawPush)
	{
		push->Draw(POS_X + 100, POS_Y + 7);
	}
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
	
	if (font)
		font->DrawTextA(spriteHandler, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

ScoreBoard* ScoreBoard::GetInstance()
{
	if (__instance == NULL)
		__instance = new ScoreBoard();
	return __instance;
}