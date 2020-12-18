#pragma once
#include "Map.h"
#include "Mario.h"
#include "Scene.h"
#include "Camera.h"
#include "Grid.h"
#include "Trigger.h"
#include "Portal.h"
#include "CheckPoint.h"
class PlayScene :public Scene
{
private:
	Mario* P;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAPS(string line);
	void _ParseSection_SETTINGS(string line);
public:
	vector<LPGAMEOBJECT> HolderObjects;
	vector<LPGAMEOBJECT> EnemyObject;
	vector<LPGAMEOBJECT> GroundObject;
	unordered_map<int,SceneGate*> listTrigger;
	unordered_map<int, Portal*> listPortal;
	vector<CheckPoint*> listPoint;
	PlayScene(int id, LPCWSTR filePath);
	void ChangeScene();
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload(); 
	Mario* GetPlayer() { return P; }
};
class PlayScenceKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	PlayScenceKeyHandler(Scene* s) : ScenceKeyHandler(s) {};
};
