#include "Camera.h"
#include "Mario.h"
#include "LimitAutoCameraState.h"
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
	typeMove = 0;
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
}
RECT Camera::GetBBox()
{
	RECT bound;

	bound.left = cam_x;
	bound.top = cam_y;
	bound.right = cam_x + width;;
	bound.bottom = cam_y + height;
	return bound;
}


void Camera::Update(DWORD dt)
{
		switch (typeMove)
		{
		case 1:
			if(cam_x <= maxRightCam)
				cam_x += 1.5;
			if (player->x < cam_x) {
				player->ChangeState(new LimitAutoCameraState());
			}

			if (player->x > cam_x + GetWidth() - 96)
			{
				player->ChangeState(new LimitAutoCameraState());
			}
			break;
		case -1:
			break;
		case 2:
			break;
		case -2:
			break;
		default:
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
				if (cy >= maxBottomCam - SCREEN_HEIGHT / 2 - 32)
					cy = maxBottomCam;
			}
			SetCamPos(cx, cy);
			break;
		}
	
	
}


Camera::~Camera()
{
}
