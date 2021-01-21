#include "Alert.h"
#include "Mario.h"
#define LEFT 192
#define TOP 200
#define RIGHT 720
#define BOTTOM 400
Alert::Alert(STATEOBJECT card, float x, float y) {
	this->x = x;
	this->y = y;
	startTimeAlert = GetTickCount();
	infor = "      COURSE   CLEAR   :\n";
	infor +="\n\n";
	infor +="YOU   GOT   A   CARD";
	Item = animationsSets->Get(CARD_HUB)->Get(card);
}

Alert::~Alert()
{
}

void Alert::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
}
void Alert::Init()
{
	test = NULL;
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	SetRect(&rect, LEFT, TOP, RIGHT, BOTTOM);
	HRESULT hr = D3DXCreateFont(
		d3ddv,		// d3d divice
		25,			//	Height
		0,			//	Width
		FW_NORMAL,	//	Weight
		1,			//MipLevels
		false,		//Italic,
		DEFAULT_CHARSET, //CharSet
		OUT_DEFAULT_PRECIS, //OutputPrecision
		ANTIALIASED_QUALITY, // Quality
		DEFAULT_PITCH|FF_DONTCARE, // PitchAndFamily,
		L"Super Mario Bros. 3",
		&test);	
}
void Alert::Render() {
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
	if (test) {
		test->DrawTextA(spriteHandler, infor.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		
	}
	Item->Render(x +150, y);
}