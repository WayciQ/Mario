#pragma once
#include"GameObject.h"
#define HEIGHT_TRIGGER 32
#define WIDTH_TRIGGER 16
class Trigger : public GameObject
{
	int trigger_port;
	int SideToIn;
public:
	Trigger(int port, float w, float h, int SideToIn)
	{
		this->type = TRIGGER;
		tag = BOX;
		this->heightBBox = h;
		this->widthBBox = w;
		this->trigger_port = port;
		this->SideToIn = SideToIn;
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
	int GetTriggerPort() { return trigger_port; }
	int GetWayIn() {
		return SideToIn;
	}
};

typedef Trigger* LPPORTAL;

