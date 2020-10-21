#pragma once
#include "GameGlobal.h"
#include "Map.h"
class Camera
{
private:
	static Camera* __instance;

	int mWidth;
	int mHeight;
public:
	float cam_x;
	float cam_y;

	bool isChangePort;

	void SetCamPos(float x, float y) { this->cam_x = x; this->cam_y = y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; }

	void SetRect(int width, int height) { mWidth = width; mHeight = height; };
	RECT GetBound();
	
	int GetHeight() { return mHeight; }
	int GetWidht() { return mWidth; }
	void Update();

	static Camera* GetInstance();

	Camera();
	~Camera();
};

