#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_
class GameObject;	//Nếu include sẽ lỗi circular dependency, chỉ cần khai báo thế này
class Collider
{
private:
	float top;
	float left;
	float bottom;
	float right;
	GameObject * owner;
public:
	Collider();
	Collider(float top, float left, float bottom, float right);
	~Collider();

	//=============== GET - SET METHOD ========================
	float GetTop();
	float GetLeft();
	float GetBottom();
	float GetRight();

	void SetTop(float new_top);
	void SetLeft(float new_left);
	void SetBottom(float new_bottom);
	void SetRight(float new_right); 
	//=============== END GET - SET METHOD =====================

	void SetCollider(int top, int left, int bottom, int right);
};
#endif // !_COLLIDER_H_
