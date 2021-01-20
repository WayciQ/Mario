#pragma once
#include "GameObject.h"
class SceneGate : public GameObject
{
	int gate_id;
	int SideToIn;
	float posX, posY;
	
public:
	int typecam;
	float topScene;
	float leftScene;
	float rightScene, bottomScene;
	SceneGate(int port, 
		float w, 
		float h, 
		int SideToIn,
		float PosX, 
		float PosY, 
		float leftScene,
		float topScene, 
		float rightScene,
		float  bottomScene,
		int typeCam = 0)
	{
		this->type = SCENE_GATE;
		tag = BOX;
		SetBBox(w, h);
		this->gate_id = port;
		this->SideToIn = SideToIn;
		this->posX = PosX;
		this->posY = PosY;
		this->leftScene = leftScene;
		this->topScene = topScene;
		this->rightScene = rightScene;
		this->bottomScene = bottomScene;
		typecam = typeCam;
	};
	void Render() {
		//RenderBoundingBox();
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x;
		t = y;
		r = x + widthBBox;
		b = y + heightBBox;
	};
	int GetGateId() { return gate_id; }
	int GetWayIn() {
		return SideToIn;
	}
	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	float GetCamSet() { return topScene; }
};

