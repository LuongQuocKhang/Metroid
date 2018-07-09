#pragma once
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_


#include <d3dx9.h>
#include "Sprite.h"
#include "Collider.h"
#include "Parameters.h"
class GameObject
{
protected:
	
	World * manager;	// con trỏ đến world để thao tác với các object ở world khi cần thiết

	float pos_x;		// x postition of samus
	float pos_y;		// y position of samus
	float lastPosX;
	float lastPosY;

	float width;
	float height;

	float vx;		// x velocity
	float vy;		// y velocity

	float vx_last; // last vx of samus before stop ( to determine the direction of samus)
	float vy_last;

	LPD3DXSPRITE spriteHandler;
	
	OBJECT_TYPE type;		//Loại GameObject, được định nghĩa trong file type
	bool isActive;	// Cho biết GameObject có đang hoạt động hay không
	Sprite* sprite;
	//
	//Các thuộc tính Collision
	//
	Collider * collider;
	Collider * broadPhaseBox;

	float collisionTimeScale; // thời gian va chạm

	float normalx;	// "vector pháp tuyến" để xét va chạm
	float normaly;
	
	float gravity;
	int health;
public:
	bool isHit;

	DWORD last_time; // this is to control the animate rate of kitty
	GameObject();
	//======================== GET - SET METHOD ================================
	OBJECT_TYPE GetType();
	void SetType(OBJECT_TYPE type);

	int GetHealth();
	void SetHealth(int value);

	bool IsActive();
	void SetActive(bool value);
	void SetlastPosX(float posx);
	void SetlastPosY(float posy);
	float GetlastPosX();
	float GetlastPosY();

	float getgravity();
	void setgravity(float value);

	void SetVelocityX(float value);
	float GetVelocityX();
	void SetVelocityY(float value);
	float GetVelocityY();

	void SetPosX(int value);
	float GetPosX();
	void SetPosY(int value);
	float GetPosY();
	
	void SetVelocityXLast(float value);
	float GetVelocityXLast();
	void SetVelocityYLast(float value);
	float GetVelocityYLast();

	void SetWidth(float value);
	float GetWidth();

	void SetHeight(float value);
	float GetHeight();

	void setNormalx(float value);
	float getNormalx();
	void setNormaly(float value);
	float getNormaly();


	Collider * GetCollider();
	//===============================END GET - SET METHOD============================

	//=============================== VIRTUAL METHOD FOR INHERITANCE ================
	virtual void InitSprites();
	virtual ~GameObject();
	virtual void Update(float t);
	virtual void Render();

	
	//virtual void Reset(int x, int y);	

	//Phương thức để active lại GameObject
	virtual void Init(float posX, float posY);

	// Hủy GameObject (Lưu ý: chỉ unactive chứ không delete GameObject)
	virtual void Destroy();				

	// ============================== END VIRTUAL METHOD =============================


	// ============================== COLLISTION METHOD ==============================
	//--TO DO: Khang hoàn thiện những hàm này
	bool IsInCamera();
	bool IsCollide(GameObject* target);
	bool IsInside(GameObject* target);
	//bool IsInCamera();

	float SweptAABB(GameObject *target, const float &DeltaTime);

	// xử lý khi có va chạm
	//void Response(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);

	virtual void Response(GameObject *target, const float &DeltaTime);
	void Deflect(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	//void Push(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	//void Slide(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	virtual void SlideFromGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	// ============================== END COLLISTION METHOD ==========================
};
#endif // !_GAME_OBJECT_
