#pragma once

#include "Scene.h"
#include "PlayScene.h"
class WorldMapScene :public Scene
{
	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	Mario* P;
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public:
	WorldMapScene(int id, LPCWSTR filePath);
	~WorldMapScene() {};
	void Load();
	void Update(DWORD dt);
	void Render() ;
	void Unload();
	void Load(LPCWSTR gameFile) ;
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	int GetNumCurrentScene() { return current_scene; }
	void SwitchScene(int scene_id);
};

class WorldMapSceneKeyHandle : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	WorldMapSceneKeyHandle(Scene* s) : ScenceKeyHandler(s) {};
};
