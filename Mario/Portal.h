#pragma once
#include "GameObject.h"
class Portal : public GameObject
{
private:
	int scene_id;
public:
	Portal(int scene_id, float w, float h)
	{
		this->type = PORTAL;
		this->tag = BOX;
		this->scene_id = scene_id;
		this->widthBBox = w;
		this->heightBBox = h;
	}
	~Portal(){}
	void Update(WORD dt)
	{

	}
	void Render()
	{
		RenderBoundingBox();
	}
	void GetBoundingBox(float& l, float& t, float& b, float& r)
	{
		l = x;
		t = y;
		b = y + heightBBox;
		r = x + widthBBox;
	}
	int GetSceneId() { return scene_id; }
};

