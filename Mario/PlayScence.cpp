#include "PlayScene.h"
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Weapons.h"
#include "Bricks.h"
#include "SceneGrass.h"
#include "Box.h"
#include "Ground.h"
#include "Enemies.h"
#include "Items.h"
#include "HUB.h"
#include "Effects.h"
PlayScene::PlayScene(int id, LPCWSTR filePath) : Scene(id, filePath)
{
	key_handler = new PlayScenceKeyHandler(this);
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAPS	7
#define SCENE_SECTION_SWITCH_SCENE		8
#define SCENE_FILE_SECTION_SETTINGS 9
#define MAX_SCENE_LINE 1024


void PlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	Textures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void PlayScene::_ParseSection_MAPS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	int mapId = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	map->LoadResourses(path.c_str());
	map->SetPadding((float)atoi(tokens[3].c_str()), (float)atoi(tokens[4].c_str()));
	grid->SetSizeCell((int)atoi(tokens[2].c_str()));
	int widthmap = (int)map->GetWidthMap();
	grid->cols = (widthmap/(int)atoi(tokens[2].c_str()));
	grid->rows = ((int)map->GetHeightMap() / (int)atoi(tokens[2].c_str())) ;
	grid->Init();
	int R = atoi(tokens[5].c_str());
	int G = atoi(tokens[6].c_str());
	int B = atoi(tokens[7].c_str());
	map->backgroundcolor = D3DCOLOR_XRGB(R, G, B);
}
void PlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = Textures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}
	Sprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void PlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new Animation();
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	Animations::GetInstance()->Add(ani_id, ani);
}
void PlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int tag = atoi(tokens[0].c_str());
	int ani_set_id = atoi(tokens[1].c_str());

	TAG type = static_cast<TAG>(tag);


	if (tag == PLAYER)
	{
		TYPE type = static_cast<TYPE>(ani_set_id);
		LPANIMATION_SET set = new AnimationSet();
		for (int i = 2; i < tokens.size(); i += 2)
		{
			int ani_id = atoi(tokens[i].c_str());
			int state = atoi(tokens[i + 1].c_str());
			STATEPLAYER stateName = static_cast<STATEPLAYER>(state);
			set->Add(ani_id, stateName);
		}
		//DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		AnimationSets::GetInstance()->Add(type, set);
	}
	else
	{
		TYPE type = static_cast<TYPE>(ani_set_id);
		LPANIMATION_SET set = new AnimationSet();
		for (int i = 2; i < tokens.size(); i += 2)
		{
			int ani_id = atoi(tokens[i].c_str());
			int types = atoi(tokens[i + 1].c_str());
			STATEOBJECT type = static_cast<STATEOBJECT>(types);
			set->Add(ani_id, type);
		}
		DebugOut(L"--> %s\n", ToWSTR(line).c_str());
		AnimationSets::GetInstance()->Add(type, set);
	}
}
void PlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);


	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y
	//DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	int object_TAG = atoi(tokens[0].c_str());
	TAG  tag = static_cast<TAG>(object_TAG);

	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int type = atof(tokens[3].c_str());
	// General object setup
	GameObject* obj = NULL;

	AnimationSets* animation_sets = AnimationSets::GetInstance();
	switch (tag)
	{
	case PLAYER:
		if (P != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = player;
		P = (Mario*)obj;
		player->Revival(x, y, static_cast<TYPE>((int)atof(tokens[3].c_str())));
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case GROUND:
		switch (type)
		{
		case GROUND_LAND:
			obj = new Ground((float)atof(tokens[4].c_str()), (float)atof(tokens[5].c_str()));
			listGroundObject.push_back(obj);
			break;
		case BLOCK:
			obj = Bricks::CreateBrick(static_cast<TYPE>((int)atof(tokens[4].c_str())), y, static_cast<TYPE>((int)atof(tokens[5].c_str())), static_cast<TYPE>((int)atof(tokens[6].c_str())));
			break;
		case GRASS:
			obj = new SceneGrass();
			break;
		case GROUND_BOX:
			obj = new Box((float)atof(tokens[4].c_str()), (float)atof(tokens[5].c_str()));
			break;
		}
		
		grid->LoadObjects(obj,x,y);
		break;
	case ENEMY:
		obj = Enemies::CreateEnemy(static_cast<TYPE>(type), (float)atof(tokens[1].c_str()), (float)atof(tokens[2].c_str()));
		grid->LoadObjects(obj,x,y);
		//listEnemyObject.push_back(obj);
		break;
	case ITEM:
		obj = Items::CreateItem(static_cast<TYPE>(type), (float)atof(tokens[1].c_str()), (float)atof(tokens[2].c_str()));
		grid->AddStaticObject(obj, x, y);
		break;
	case BOX:
		switch (type)
		{
		case SCENE_GATE:
		{
			SceneGate* trigger = new SceneGate((int)atof(tokens[4].c_str()),
				(int)atof(tokens[5].c_str()),
				(int)atof(tokens[6].c_str()),
				(int)atof(tokens[7].c_str()),
				(int)atof(tokens[8].c_str()),
				(int)atof(tokens[9].c_str()),
				(int)atof(tokens[10].c_str()),
				(int)atof(tokens[11].c_str()),
				(int)atof(tokens[12].c_str()),
				(int)atof(tokens[13].c_str()));
			listTrigger[(int)atof(tokens[4].c_str())] = trigger;
			grid->AddStaticObject(trigger, x, y);
			break;
		}
		case PORTAL:
		{
			Portal* portal = new Portal((int)atof(tokens[4].c_str()),
				(int)atof(tokens[5].c_str()),
				(int)atof(tokens[6].c_str()));

			listPortal[(int)atof(tokens[4].c_str())] = portal;
			grid->AddStaticObject(portal, x, y);
			break;
		}
		case CHECKPOINT:
		{
			CheckPoint* point = new CheckPoint();
			grid->AddStaticObject(point, x, y);
			break;
		}
		}
		break;
	case EFFECT:
		obj = Effects::CreateEffect(static_cast<TYPE>(type));
		grid->AddStaticObject(obj, x, y);
		break;
	default:
		
		DebugOut(L"[ERR] Invalid object TAG: %d\n", object_TAG);
		return;
	}
	
	/*if (tag != PLAYER)
	{
		int type_ani = static_cast<TYPE>(type) == BLOCK ? atoi(tokens[4].c_str()) : atoi(tokens[3].c_str());
		TYPE types = static_cast<TYPE>(type_ani);
		LPANIMATION_SET ani_set = animation_sets->Get(types);
		obj->SetAnimationSet(ani_set);
	}*/
	
	//DebugOut(L"[INFO] Object size: %d\n", HolderObjects.size());
}
void PlayScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;
	if (tokens[0] == "time")
	{
		player->infor->SetGameTime(int(atoi(tokens[1].c_str())));
	}
	if (tokens[0] == "cam")
	{
		camera->SetCamScene(int(atoi(tokens[1].c_str())), int(atoi(tokens[2].c_str())), int(atoi(tokens[3].c_str())) - camera->GetWidth(), int(atoi(tokens[4].c_str())));
		camera->SetCamMove(int(atoi(tokens[5].c_str())));
	}
	if (tokens[0] == "scene") {
		TypeScene = int(atoi(tokens[1].c_str()));
	}
	
}
void PlayScene::Load()
{

	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		
		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAPS]") {
			section = SCENE_SECTION_MAPS; continue;
		}
		if (line == "[SETTINGS]") {
			section = SCENE_FILE_SECTION_SETTINGS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }
		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAPS: _ParseSection_MAPS(line); break;
		case SCENE_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		}
	}
	 //Init();
	f.close();
	if(TypeScene > 0)
		scoreBoard->Init();
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void PlayScene::Update(DWORD dt)
{
	ChangeScene();
	vector<LPGAMEOBJECT> coObjects;
	coObjects.clear();
	grid->UpdateCellInViewPort();
	//player->CollisonGroundWall(dt, &listGroundObject);

	for (auto& obj : listGroundObject) {
		coObjects.push_back(obj);
	}
	for (auto& obj : grid->GetObjectInViewPort()) {
		coObjects.push_back(obj);
	}
	player->Update(dt, &coObjects);
	for (auto& obj : grid->GetObjectInViewPort())
	{
		if(!player->freeze)
			obj->Update(dt, &coObjects);
	}
	
	camera->Update(dt);
	scoreBoard->Update(dt);
}

void PlayScene::Render()
{
	Map::GetInstance()->Render();

	for (auto& obj : grid->GetObjectInViewPort())
	{
		obj->Render();
	}
	player->Render();
	if (TypeScene != 0) {
		scoreBoard->Render();
	}
	
	//grid->RenderCell();
}

void PlayScene::Unload()
{
	for (auto& obj : listPoint)
		delete obj;
	
	for (int i = 0; i < listPortal.size(); i++)
		delete listPortal[i];
	
	for (int i = 0; i < listTrigger.size(); i++)
		delete listTrigger[i];

	for (auto& obj : listGroundObject)
		delete obj;

	listGroundObject.clear();
	listPoint.clear();
	listPortal.clear();
	listTrigger.clear();
	P = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}
void PlayScene::ChangeScene() {

	if (player->IsChangeTrigger) {
		auto trigger = listTrigger.at(player->infor->GetGateId());
		player->SetPosition(trigger->GetPosX(), 
							trigger->GetPosY());
		player->SetSpeed(0, 0);
		player->IsTouchTrigger = false;
		camera->SetCamScene(trigger->leftScene,trigger->topScene,trigger->rightScene - camera->GetWidth(),trigger->bottomScene);
		player->IsChangeTrigger = false;
	}

	if (player->IsChangeScene) {
		player->IsChangeScene = false;
		game->SwitchScene(player->infor->GetSceneId());
	}
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	Mario* mario = ((PlayScene*)scene)->GetPlayer();
	keyCode[KeyCode] = true;
	mario->OnKeyDown(KeyCode);
	
	if (((PlayScene*)scene)->GetTypeScene() == 0) {
		if(KeyCode == DIK_W)
		game->SwitchScene(0);
	}
}

void PlayScenceKeyHandler::KeyState(BYTE* states)
{

}
void PlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	Mario* mario = ((PlayScene*)scene)->GetPlayer();
	keyCode[KeyCode] = false;
	mario->OnKeyUp(KeyCode);
}

