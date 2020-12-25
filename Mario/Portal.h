#pragma once
#include "GameObject.h"
class Portal : public GameObject
{
	int scene_id;
public:
	Portal(int scene_id, float w, float h)
	{
		type = PORTAL;
		tag = BOX;
		this->scene_id = scene_id;
		SetBBox(w, h);
	}
	void Render()
	{
		//RenderBoundingBox();
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x;
		top = y;
		right = x + widthBBox;
		bottom = y + heightBBox;
	}
	int GetSceneId() { return scene_id; }
};

