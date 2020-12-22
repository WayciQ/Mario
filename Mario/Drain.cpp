#include "Drain.h"
Drain::Drain(float w, float h)
{
	tag = GROUND;
	type = GRASS;
	this->widthBBox = w;
	this->heightBBox = h;
}

Drain::~Drain(){}
void Drain::Render()
{
	//RenderBoundingBox();
}

void Drain::Update(){}

void Drain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + widthBBox;
	b = y + heightBBox;
}