#include "Ground.h"
Ground::Ground(float w, float h)
{
	tag = GROUND;
	type = BRICK;
	this->width = w;
	this->height = h;
}
void Ground::Render()
{
	//RenderBoundingBox();
}
void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}