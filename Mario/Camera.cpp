#include "Camera.h"
#include "Mario.h"
Camera* Camera::__instance = NULL;

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
	cx -= SCREEN_WIDTH / 2;
	
	if (cx <= 0)
	{
		cx = 0;
	}
	else if(cx + width >= Map::GetInstance()->GetWidthMap())
	{
		cx = Map::GetInstance()->GetWidthMap() - width;
	}
	
	if (cy <= SCREEN_HEIGHT)
	{
		if (cy <= 0)
			cy = 0;
		else
		cy -= SCREEN_HEIGHT / 2;
	}
	else cy = CAMERA_SCREEN;

	SetCamPos(cx, cy);
}


Camera::~Camera()
{
}
