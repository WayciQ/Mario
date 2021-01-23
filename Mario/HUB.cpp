#include "HUB.h"
#include "Mario.h"
#include "Camera.h"
#define HEIGHT_SCORE_BROAD 84
#define ID_TEX_HUB 7
#define POS_X camera->cam_x + 48
#define POS_Y camera->cam_y + 576
#define POS_I1 POS_X + 480
#define POS_I2 POS_X + 549
#define POS_I3 POS_X + 618
#define POS_X_TP POS_X + 12
#define POS_Y_TP POS_Y + 48
#define POS_Y_TEX1 POS_Y + 18
#define POS_Y_TEX2 POS_Y + 45
HUB* HUB::__instance = NULL;
HUB::HUB() {
	isDrawPush = true;
	information = "4                              01\n";
	information += "4   1241241       121\n";
	font = NULL;
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 buffer = Game::GetInstance()->GetBackBuffer();
	AddFontResourceEx(L"resource\\font\\Super-Mario-Bros--3.ttf", FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		d3ddv,		// d3d divice
		27,			//	Height
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

	

	auto sprites = Sprites::GetInstance();
	auto animation = Animations::GetInstance();
	hub = sprites->Get(90000);
	Item1 = animationsSets->Get(CARD)->Get(CARD_EMPTY);
	Item2 = animationsSets->Get(CARD)->Get(CARD_EMPTY);
	Item3 = animationsSets->Get(CARD)->Get(CARD_EMPTY);
	typePlayer = sprites->Get(92001);
	speed = sprites->Get(91001);
	push = animation->Get(91002);
}
void HUB::Init()
{
	SetRect(&rect, POS_X + 117+ map->padding_left, POS_Y_TEX1, POS_X + SCREEN_WIDTH, POS_Y + 90);
}
void HUB::Update(float dt)
{
	string scoregame = to_string(player->infor->GetScorePoint());
	while (scoregame.length() < 7)
		scoregame = "0" + scoregame;
	string timeString = to_string(player->infor->GetGameTime());
	while (timeString.length() < 3)
		timeString = "0" + timeString;

	string life = to_string(player->infor->GetLife());

	string money = to_string(player->infor->GetMoney());
	while (money.length() < 2)
		money = "  " + money;

	string scene = to_string(game->GetNumCurrentScene());

	float vx,vy;
	player->GetSpeed(vx, vy);
	if (player->isRunning)
		NumSpeed = NumSpeed > 6 ? 6 : abs(int(vx/ 0.08));
	else NumSpeed = 0;

	information = scene + "                                 " + money + "\n";
	information += life +"   "+ scoregame +"       "+ timeString +"\n";
	Item1 = animationsSets->Get(CARD_HUB)->Get(player->infor->GetCard(1));
	Item2 = animationsSets->Get(CARD_HUB)->Get(player->infor->GetCard(2));
	Item3 = animationsSets->Get(CARD_HUB)->Get(player->infor->GetCard(3));
}
void HUB::Render()
{
	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_HUB);
	Game::GetInstance()->Draw(POS_X, POS_Y - map->padding_top, bbox, 0, 0, camera->GetWidth(), 256, 255);
	
	hub->Draw(POS_X, POS_Y - map->padding_top);
	Item1->Render(POS_I1, POS_Y - map->padding_top);
	Item2->Render(POS_I2, POS_Y - map->padding_top);
	Item3->Render(POS_I3, POS_Y - map->padding_top);
	typePlayer->Draw(POS_X + 12, POS_Y + 45 - map->padding_top);
	for(int i = 0; i < NumSpeed; i++)
	{
		speed->Draw(POS_X + 156 + (i*24), POS_Y + 21 - map->padding_top);
	}

	if (NumSpeed >= 6)
	{
		push->Render(POS_X + 300, POS_Y + 21 - map->padding_top);
	}

	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
	
	if (font)
		font->DrawTextA(spriteHandler, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}

HUB* HUB::GetInstance()
{
	if (__instance == NULL)
		__instance = new HUB();
	return __instance;
}