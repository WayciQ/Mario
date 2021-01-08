#include "Alert.h"
#include "Mario.h"
Alert::Alert(STATEOBJECT card, float x, float y) {
	this->card = card;
	font = NULL;
	SetRect(&r, x, y, x + 112, y + 60);
	LPDIRECT3DDEVICE9 d3ddv = Game::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 buffer = Game::GetInstance()->GetBackBuffer();
	//AddFontResourceEx(L"resource\\font\\Super-Mario-Bros--3.ttf", FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		d3ddv,		// d3d divice
		20,			//	Height
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
	startTimeAlert = GetTickCount();
}

void Alert::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
	if (GetTickCount() - startTimeAlert > 1000) {
		LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
		
		/*if (font)
			font->DrawTextA(spriteHandler,"COURSE CLEAR!", -1, &r, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));*/
	}

	
	SetRect(&r, player->x, player->y - 100, player->x + 120, player->y - 40);
	
}
void Alert::Render() {
	LPD3DXSPRITE spriteHandler = Game::GetInstance()->GetSpriteHandler();
	if (font)
		font->DrawTextA(spriteHandler, "COURSE CLEAR!", -1, &r, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}