#include "Ground.h"
Ground::Ground(float w, float h)
{
	tag = GROUND;
	type = GROUND_LAND;
	this->widthBBox = w;
	this->heightBBox = h;
}
void Ground::Render()
{
	//RenderBoundingBox();
}
void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}