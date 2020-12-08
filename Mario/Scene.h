#pragma once
#include "KeyEventHandler.h"
#include "GameGlobal.h"
class Scene
{
protected:
	KeyEventHandler* key_handler;
	int id;
	LPCWSTR sceneFilePath;
	void _ParseSection_TEXTURES(string line) {};
	void _ParseSection_SPRITES(string line) {};
	void _ParseSection_ANIMATIONS(string line) {};
	void _ParseSection_ANIMATION_SETS(string line) {};
	void _ParseSection_OBJECTS(string line) {};
	void _ParseSection_MAPS(string line) {};
	void _ParseSection_SWITCHSCENE(string line) {};
public:
	Scene(int id, LPCWSTR filePath);

	KeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef Scene* LPSCENE;

class ScenceKeyHandler : public KeyEventHandler
{
protected:
	Scene* scene;

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	ScenceKeyHandler(Scene* s) : KeyEventHandler() { scene = s; }
};