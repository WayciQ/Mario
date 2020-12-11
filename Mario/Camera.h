#pragma once
#include "GameGlobal.h"
#include "Map.h"
class Camera
{
private:
	static Camera* __instance;
	
	
	int width; // width screen
	int height; // height screen
public:
	float cam_x; // cam_x
	float cam_y; // cam_y
	int maxTopCam;
	int maxLeftCam;
	int maxRightCam;
	int maxBottomCam;
	Camera();
	~Camera();

	void SetCamPos(float x, float y) { this->cam_x = x; this->cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }
	void SetRect(int width, int height) { width = width; height = height; };
	RECT GetBound(); // get RECT topScene
	
	int GetHeight() { return height; }
	int GetWidth() { return width; }
	void SetCamScene(float l, float t, float r, float b) { maxLeftCam = l; maxTopCam = t; maxRightCam = l + r; maxBottomCam = b; }
	void Update();

	static Camera* GetInstance();

};

