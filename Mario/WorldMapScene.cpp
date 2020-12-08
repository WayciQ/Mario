#include "WorldMapScene.h"
#include "PlayScene.h"
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAPS	7
#define SCENE_SECTION_SWITCH_SCENE		8
#define MAX_SCENE_LINE 1024

WorldMapScene::WorldMapScene(int id, LPCWSTR filePath) : Scene(id, filePath)
{
	key_handler = new WorldMapSceneKeyHandle(this);
}
void WorldMapScene::_ParseSection_SETTINGS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	if (tokens[0] == "start")
		current_scene = atoi(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting %s\n", ToWSTR(tokens[0]).c_str());
}

void WorldMapScene::_ParseSection_SCENES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	int id = atoi(tokens[0].c_str());
	LPCWSTR path = ToLPCWSTR(tokens[1]);

	LPSCENE scene = new PlayScene(id, path);
	scenes[id] = scene;
}
void WorldMapScene::Load()
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
		if (line == "[SWITCHSCENE]") {
			section = SCENE_SECTION_SWITCH_SCENE; continue;
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
		case SCENE_SECTION_SWITCH_SCENE: _ParseSection_SWITCHSCENE(line); break;
		}
	}
	//Init();
	f.close();
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}
void WorldMapScene::Load(LPCWSTR gameFile)
{
	DebugOut(L"[INFO] Start loading game file : %s\n", gameFile);

	ifstream f;
	f.open(gameFile);
	char str[MAX_GAME_LINE];

	// current resource section flag
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (f.getline(str, MAX_GAME_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SETTINGS]") { section = GAME_FILE_SECTION_SETTINGS; continue; }
		if (line == "[SCENES]") { section = GAME_FILE_SECTION_SCENES; continue; }

		//
		// data section
		//
		switch (section)
		{
		case GAME_FILE_SECTION_SETTINGS: _ParseSection_SETTINGS(line); break;
		case GAME_FILE_SECTION_SCENES: _ParseSection_SCENES(line); break;
		}
	}
	f.close();

	DebugOut(L"[INFO] Loading game file : %s has been loaded successfully\n", gameFile);

	SwitchScene(current_scene);
}
void WorldMapScene::SwitchScene(int scene_id)
{
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);

	scenes[current_scene]->Unload();

	Textures::GetInstance()->Clear();
	Sprites::GetInstance()->Clear();
	Animations::GetInstance()->Clear();
	AnimationSets::GetInstance()->Clear();
	current_scene = scene_id;
	LPSCENE s = scenes[scene_id];
	Game::GetInstance()->SetKeyHandler(s->GetKeyEventHandler()); //nhan ban phim moi
	s->Load();
}
void WorldMapScene::_ParseSection_TEXTURES(string line)
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
void WorldMapScene::_ParseSection_SPRITES(string line)
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
void WorldMapScene::_ParseSection_ANIMATIONS(string line)
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
void WorldMapScene::_ParseSection_ANIMATION_SETS(string line)
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
void WorldMapScene::_ParseSection_OBJECTS(string line)
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
		player->Revival(x, y);
		DebugOut(L"[INFO] Player object created!\n");
		break;
	}

	if (tag != PLAYER)
	{
		int type_ani = static_cast<TYPE>(type) == BLOCK ? atoi(tokens[4].c_str()) : atoi(tokens[3].c_str());
		TYPE types = static_cast<TYPE>(type_ani);
		LPANIMATION_SET ani_set = animation_sets->Get(types);
		obj->SetAnimationSet(ani_set);
	}

}

void WorldMapScene::Update(DWORD dt)
{
	GetCurrentScene()->Update(dt);
}
void WorldMapScene::Render()
{
	GetCurrentScene()->Render();
}
void WorldMapScene::Unload() 
{

}
void WorldMapSceneKeyHandle::OnKeyDown(int KeyCode)
{
	/*Mario* mario = ((PlayScene*)scene)->GetPlayer();*/
	/*keyCode[KeyCode] = true;
	mario->OnKeyDown(KeyCode);*/
}

void WorldMapSceneKeyHandle::KeyState(BYTE* states)
{

}
void WorldMapSceneKeyHandle::OnKeyUp(int KeyCode)
{
	/*Mario* mario = ((PlayScene*)scene)->GetPlayer();*/
	/*keyCode[KeyCode] = false;
	mario->OnKeyUp(KeyCode);*/
}