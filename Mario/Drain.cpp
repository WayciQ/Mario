#include "Drain.h"
Drain::Drain(STATEOBJECT types, float w, float h)
{
	tag = GROUND;
	type = DRAIN;
	this->typeDrain = types;
	this->width = w;
	this->height = h;
}

Drain::~Drain(){}
void Drain::Render()
{
	RenderBoundingBox();
}

void Drain::Update(){}

void Drain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}