#pragma once
#include"GameObject.h"
class Portal : public GameObject
{
	int scene_id;
public:
	Portal(int scene_id, float w, float h)
	{
		this->heightBBox = h;
		this->widthBBox = w;
		this->scene_id = scene_id;
	};
	void Render() {};
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x;
		t = y;
		r = x + widthBBox;
		b = y + heightBBox;
	};
	int GetSceneId() { return scene_id; }

};

