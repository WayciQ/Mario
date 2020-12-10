#pragma once
#include "GameObject.h"
class Portal : public GameObject
{

	int scene_id;
public:
	Portal(int scene_id, float w, float h,float x,float y)
	{
		this->type = PORTAL;
		tag = BOX;
		this->scene_id = scene_id;
		this->widthBBox = w;
		this->heightBBox = h;
		this->x = x;
		this->y = y;
	}
	void Render()
	{
		RenderBoundingBox();
	}
	void GetBoundingBox(float& l, float& t, float& b, float& r)
	{
		l = x;
		t = y;
		r = x + widthBBox;
		b = y + heightBBox;
	}
	int GetSceneId() { return scene_id; }
};

