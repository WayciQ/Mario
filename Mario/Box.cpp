#include "Box.h"

Box::Box(float w, float h)
{
	tag = GROUND;
	type = BOX_GROUND;
	widthBBox = w;
	heightBBox = h;
}

Box::~Box() {}
void Box::Render()
{
	//RenderBoundingBox();
}

void Box::Update() {}

void Box::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}