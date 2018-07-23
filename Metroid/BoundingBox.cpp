#include "BoundingBox.h"



BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(float new_x, float new_y, float new_width, float new_height)
{
	x = new_x;
	y = new_y;
	width = new_width;
	height = new_height;
}


BoundingBox::~BoundingBox()
{
}

float BoundingBox::GetX()
{
	return x;
}

float BoundingBox::GetY()
{
	return y;
}

float BoundingBox::GetWidth()
{
	return width;
}

float BoundingBox::GetHeight()
{
	return height;
}

void BoundingBox::SetX(float new_x)
{
	x = new_x;
}

void BoundingBox::SetY(float new_y)
{
	y = new_y;
}

void BoundingBox::SetWidth(float new_width)
{
	width = new_width;
}

void BoundingBox::SetHeight(float new_height)
{
	height = new_height;
}

void BoundingBox::SetBoundingBox(float new_x, float new_y, float new_width, float new_height)
{
	x = new_x;
	y = new_y;
	width = new_width;
	height = new_height;
}
