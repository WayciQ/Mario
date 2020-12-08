#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "GameGlobal.h"
#include <dinput.h>
#include "Scene.h"
#define KEYBOARD_BUFFER_SIZE 1024
#define DIRECTINPUT_VERSION 0x0800

using namespace std;

class Game
{
	static Game* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	int screen_width;
	int screen_height;


	unordered_map<int, LPSCENE> scenes;
	int current_worldMap;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_WORLDMAPS(string line);
public:
	void InitKeyboard();
	void Init(HWND hWnd);
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void DrawFlip(float x, float y, LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2& vtScale, int left, int top, int right, int bottom, int alpha = 255);
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_worldMap]; }
	int GetNumCurrentScene() { return current_worldMap; }
	void SwitchWorldMap(int scene_id);

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }


	static Game* GetInstance();

	~Game();

};

