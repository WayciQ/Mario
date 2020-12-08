#pragma once
#include"GameObject.h"
class Portal : public GameObject
{
	int scene_id;
	float Cy;
public:
	Portal(int scene_id, float w, float h,float cy)
	{
		this->type = PORTAL;
		tag = BOX;
		this->heightBBox = h;
		this->widthBBox = w;
		this->scene_id = scene_id;
		Cy = cy;
	};
	void Render() {
		RenderBoundingBox();
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x;
		t = y;
		r = x + widthBBox;
		b = y + heightBBox;
	};
	int GetSceneId() { return scene_id; }
	int GetCy() { return Cy; }
};

typedef Portal* LPPORTAL;

