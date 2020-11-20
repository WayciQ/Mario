#include "Drain.h"
Drain::Drain(float w, float h)
{
	tag = GROUND;
	type = DRAIN;
	this->width = w;
	this->height = h;
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
	r = x + width;
	b = y + height;
}