#include "Camera.h"
#include "Mario.h"
Camera* Camera::__instance = NULL;

#define CAMERA_SCREEN_HIGHT	248
#define CAMERA_SCREEN_HIGHT_MAX	200
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
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
}
RECT Camera::GetBound()
{
	RECT bound;

	bound.left = cam_x;
	bound.top = cam_y;
	bound.right = cam_x + width;;
	bound.bottom = cam_y + height;
	return bound;
}

void Camera::Update()
{
	float cx, cy;
	player->GetPosition(cx, cy);
	cx -= width / 2;
	cy -= height / 2;
	if (cx <= maxLeftCam)
	{
		cx = maxLeftCam;
	}
	else if(cx >= maxRightCam )
	{
		cx = maxRightCam ;
	}
	else 
	{
		if (cy >= maxRightCam - SCREEN_HEIGHT / 2)
			cy = cx = maxRightCam;
		;
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
		if(cy >= maxBottomCam - SCREEN_HEIGHT / 2)
			cy  = maxBottomCam;
	}
	SetCamPos(cx, cy);
}


Camera::~Camera()
{
}
