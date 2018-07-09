#include "Collider.h"



Collider::Collider()
{
}

Collider::Collider(float top, float left, float bottom, float right)
{
	this->top = top;
	this->left = left;
	this->bottom = bottom;
	this->right = right;
}


Collider::~Collider()
{
}

float Collider::GetTop()
{
	return top;
}

float Collider::GetLeft()
{
	return left;
}

float Collider::GetBottom()
{
	return bottom;
}

float Collider::GetRight()
{
	return right;
}

void Collider::SetTop(float new_top)
{
	top = new_top;
}

void Collider::SetLeft(float new_left)
{
	left = new_left;
}

void Collider::SetBottom(float new_bottom)
{
	bottom = new_bottom;
}

void Collider::SetRight(float new_right)
{
	right = new_right;
}

void Collider::SetCollider(int top, int left, int bottom, int right)
{
	this->top = top;
	this->left = left;
	this->bottom = bottom;
	this->right = right;
}
