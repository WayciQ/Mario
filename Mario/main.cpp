/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include "debug.h"
#include <d3dx9.h>
#include <d3d9.h>
#include "Map.h"
#include "Game.h"
#include "Textures.h"
#include "GameGlobal.h"
#include "Mario.h"
#include "PlayerStandingState.h"
#include "Brick.h"
#include "Goomba.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0
#define ID_TEX_MARIO 1

#define ID_TEX_ENEMY 11
#define ID_TEX_MISC 22
#define ID_TEX_FIRE 33

Map* map = Map::GetInstance();
Game* game;
vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public KeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	keyCode[KeyCode] = true;
	player->OnKeyDown(KeyCode);
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	keyCode[KeyCode] = false;
	player->OnKeyUp(KeyCode);

	//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	

}


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	
	Textures* textures = Textures::GetInstance();
	textures->LoadResources();
	Sprites* sprites = Sprites::GetInstance();
	sprites->LoadResources();
	Animations* animations = Animations::GetInstance();
	animations->LoadResources();
	/*LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);*/
	Map::GetInstance()->LoadResourses();

	
	LevelMario* marioLevel = LevelMario::GetInstance();
	LPMARIOLEVEL level;
	level = new CLevel();
	level->Add(121, STANDING_RIGHT);
	level->Add(122, STANDING_LEFT);		// idle left
	level->Add(221, WALKING_RIGHT);		// walk right
	level->Add(222, WALKING_LEFT);		// walk left
	level->Add(223, WALKING_FAST_RIGHT);
	level->Add(224, WALKING_FAST_LEFT);
	level->Add(225, RUNNING_RIGHT);
	level->Add(226, RUNNING_LEFT);
	level->Add(320, FALLING_RIGHT);		// fall right
	level->Add(321, FALLING_LEFT);		// fall left
	level->Add(322, JUMPING_RIGHT);		// jump right
	level->Add(323, JUMPING_LEFT);		// jump left
	level->Add(324, SITTING_RIGHT);		// sit right
	level->Add(325, SITTING_LEFT);		// sit left
	level->Add(326, LAST_RIGHT);
	level->Add(327, LAST_LEFT);
	level->Add(421, WHIPPING_RIGHT); 		// fight right
	level->Add(422, WHIPPING_LEFT);		// fight left
	
	marioLevel->Add(RACCOON, level);

	level = new CLevel();
	level->Add(101, STANDING_RIGHT);
	level->Add(102, STANDING_LEFT);		// idle left
	level->Add(201, WALKING_RIGHT);		// walk right
	level->Add(202, WALKING_LEFT);		// walk left
	level->Add(203, WALKING_FAST_RIGHT);
	level->Add(204, WALKING_FAST_LEFT);
	level->Add(205, RUNNING_RIGHT);
	level->Add(206, RUNNING_LEFT);
	level->Add(300, FALLING_RIGHT);		// fall right
	level->Add(301, FALLING_LEFT);		// fall left
	level->Add(302, JUMPING_RIGHT);		// jump right
	level->Add(303, JUMPING_LEFT);		// jump left
	level->Add(306, LAST_RIGHT);
	level->Add(307, LAST_LEFT);
	
	marioLevel->Add(SMALL, level);

	level = new CLevel();
	level->Add(111, STANDING_RIGHT);
	level->Add(112, STANDING_LEFT);		// idle left
	level->Add(211, WALKING_RIGHT);		// walk right
	level->Add(212, WALKING_LEFT);		// walk left
	level->Add(213, WALKING_FAST_RIGHT);
	level->Add(214, WALKING_FAST_LEFT);
	level->Add(215, RUNNING_RIGHT);
	level->Add(216, RUNNING_LEFT);
	level->Add(310, FALLING_RIGHT);		// fall right
	level->Add(311, FALLING_LEFT);		// fall left
	level->Add(312, JUMPING_RIGHT);		// jump right
	level->Add(313, JUMPING_LEFT);		// jump left
	level->Add(314, SITTING_RIGHT);		// sit right
	level->Add(315, SITTING_LEFT);		// sit left
	level->Add(316, LAST_RIGHT);
	level->Add(317, LAST_LEFT);
	marioLevel->Add(BIG, level);


	player->SetPosition(270, 200);
	player->ChangeAnimation(new PlayerStandingState());
	objects.push_back(player);
	
	/*for (int i = 0; i < 5; i++)
	{
		Brick* brick = new Brick();
		brick->AddAnimation(801);
		brick->SetPosition(100.0f + i * 60.0f, 74.0f);
		objects.push_back(brick);

		brick = new Brick();
		brick->AddAnimation(801);
		brick->SetPosition(100.0f + i * 60.0f, 90.0f);
		objects.push_back(brick);

		brick = new Brick();
		brick->AddAnimation(801);
		brick->SetPosition(84.0f + i * 60.0f, 90.0f);
		objects.push_back(brick);
	}*/


	for (int i = 0; i < 150; i++)
	{
		Brick* brick = new Brick();
		brick->AddAnimation(801,BRICK);
		brick->SetPosition(0 + i * 16.0f, 300);
		objects.push_back(brick);
	}
	for (int i = 0; i < 2; i++)
	{
		Brick* brick = new Brick();
		brick->AddAnimation(801, BRICK);
		brick->SetPosition(150, 284 - i*16.0f);
		objects.push_back(brick);
	}
	for (int i = 0; i < 2; i++)
	{
		Brick* brick = new Brick();
		brick->AddAnimation(801, BRICK);
		brick->SetPosition(350, 284 - i * 16.0f);
		objects.push_back(brick);
	}
	

	
	//// and Goombas 
	//for (int i = 0; i < 4; i++)
	//{
	//	Goomba* goomba = new Goomba();
	//	goomba->AddAnimation(701,GOOMBA);
	//	goomba->AddAnimation(702,GOOMBA_DIE);
	//	goomba->SetPosition(170 + i * 14.0f, 200);
	//	objects.push_back(goomba);
	//}

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
		
	}
	


	// Update camera to follow mario
	
	Map::GetInstance()->Update(dt);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		Map::GetInstance()->Render();
		
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = Game::GetInstance();
	game->Init(hWnd);
	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}