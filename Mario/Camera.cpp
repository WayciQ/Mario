#include "Camera.h"
#include "Mario.h"
#include "LimitAutoCameraState.h"
#include "PlayerChangeLevelState.h"
Camera* Camera::__instance = NULL;
#define HEIGHT_SCREEN_GAME 576
Camera* Camera::GetInstance()
{
	if (__instance == NULL)
		__instance = new Camera();
	return __instance;
}

Camera::Camera()
{
	cam_x = 0;
	cam_y = 0;
	typeMove = 0;
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
}
RECT Camera::GetBBox()
{
	RECT bound;
	bound.left = cam_x;
	bound.top = cam_y;
	bound.right = cam_x + SCREEN_WIDTH;
	bound.bottom = cam_y + SCREEN_HEIGHT;
	return bound;
}


void Camera::Update(DWORD dt)
{
	if (typeMove == 1) {
		if (cam_x <= maxRightCam)
			cam_x += 1.5;
		if (player->x < cam_x) {
			player->ChangeState(new LimitAutoCameraState());
		}

		if (player->x > cam_x + SCREEN_WIDTH - 48)
		{
			player->x = cam_x + SCREEN_WIDTH - 48;
		}
	}
	else if (typeMove == 2) {
		SetCamPos(0, 0);
	}
	else {
		
		float cx, cy;
		player->GetPosition(cx, cy);
		cx -= width / 2;
		cy -= height / 2;
		if (cx <= maxLeftCam)
		{
			cx = maxLeftCam;
		}
		else if (cx >= maxRightCam)
		{
			cx = maxRightCam;
		}

		if (cy <= maxTopCam)
		{
			cy = maxTopCam;
		}
		else if (cy >= maxBottomCam)
		{
			cy = maxBottomCam;
		}
		else
		{
			if (cy >= maxBottomCam - HEIGHT_SCREEN_GAME)
				cy = maxBottomCam;
		}
		SetCamPos(cx, cy);
	}
	if (player->y > cam_y + HEIGHT_SCREEN_GAME) {
		player->infor->LifeEarn(-1);
		player->infor->SetSceneId(0);
		player->IsChangeScene = true;
	}
}


Camera::~Camera()
{
}
