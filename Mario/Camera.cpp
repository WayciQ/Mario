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
	this->mWidth = SCREEN_WIDTH;
	this->mHeight = SCREEN_HEIGHT;
}
RECT Camera::GetBound()
{
	RECT bound;

	bound.left = cam_x;
	bound.top = cam_y;
	bound.right = cam_x + mWidth;;
	bound.bottom = cam_y + mHeight;
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
	else if(cx + mWidth >= Map::GetInstance()->GetWidthMap())
	{
		cx = Map::GetInstance()->GetWidthMap() - mWidth;
	}
	
	if (cy <= 224)
	{
		cy -= SCREEN_HEIGHT / 2;
	}
	else
		cy = 264;
	SetCamPos(cx, cy);
}


Camera::~Camera()
{
}
