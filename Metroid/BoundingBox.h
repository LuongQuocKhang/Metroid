#pragma once
#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

class BoundingBox
{
private:
	float x, y;
	float width, height;
public:
	BoundingBox();
	BoundingBox(float new_x, float new_y, float new_width, float new_height);
	~BoundingBox();

	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();

	void SetX(float new_x);
	void SetY(float new_y);
	void SetWidth(float new_width);
	void SetHeight(float new_height);

	void SetBoundingBox(float new_x, float new_y, float new_width, float new_height);
};

#endif // !_BOUNDINGBOX_H_

