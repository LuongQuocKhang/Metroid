#pragma once
#ifndef _SAMUS_H
#define _SAMUS_H_
#include "Sprite.h"
#include "Parameters.h"
#include "GameObject.h"
#include "trace.h"
#include "Camera.h"
#include "BulletObject.h"

enum SAMUS_STATE {
	APPEARANCE,
	IDLE_LEFT,
	IDLE_RIGHT,
	LEFTING,
	RIGHTING,
	IDLING_AIM_UP_LEFT,
	IDLING_AIM_UP_RIGHT,
	AIMING_UP_LEFT,
	AIMING_UP_RIGHT,
	ON_MORPH_LEFT,
	ON_MORPH_RIGHT,
	ON_RUN_SHOOTING_LEFT,
	ON_RUN_SHOOTING_RIGHT,
	ON_JUMP_LEFT,
	ON_JUMP_RIGHT,
	ON_SOMERSAULT_LEFT,
	ON_SOMERSAULT_RIGHT,
	ON_JUMPING_SHOOTING_LEFT,
	ON_JUMPING_SHOOTING_RIGHT,
	ON_JUMP_AIM_UP_LEFT,
	ON_JUMP_AIM_UP_RIGHT,
	IDLING_SHOOTING_LEFT,
	IDLING_SHOOTING_RIGHT,
	IDLING_SHOOTING_UP_LEFT,
	IDLING_SHOOTING_UP_RIGHT,
	ON_JUMP_SHOOTING_UP_LEFT,
	ON_JUMP_SHOOTING_UP_RIGHT,
};
class Samus : public GameObject
{
protected:
	Sprite * appearing;
	Sprite * running_left;
	Sprite * running_right;
	Sprite * jump_left;
	Sprite * jump_right;
	Sprite * run_shooting_left;
	Sprite * run_shooting_right;
	Sprite * run_aim_up_left;
	Sprite * run_aim_up_right;
	Sprite * idle_aim_up_left;
	Sprite * idle_aim_up_right;
	Sprite * idle_left;
	Sprite * idle_right;
	Sprite * morph_ball_left;
	Sprite * morph_ball_right;
	Sprite * somersault_left;
	Sprite * somersault_right;
	Sprite * jumping_shooting_left;
	Sprite * jumping_shooting_right;
	Sprite * jump_aim_up_left;
	Sprite * jump_aim_up_right;
	Sprite * idle_shooting_left;
	Sprite * idle_shooting_right;
	Sprite * idle_shooting_up_left;
	Sprite * idle_shooting_up_right;
	Sprite * jump_shooting_up_left;
	Sprite * jump_shooting_up_right;

	SAMUS_STATE state;

	BulletObject ** listBullet;
	int num;
	bool isMorph;	// Kiểm tra xem Samus đã nhặt Morph ball Item chưa để có thể crouch
	int missile_numbers;		//số lượng missile ban đầu
	int boom_numbers;					
public:
	float health;	// Máu của Samus
	bool isDeath;	// Trạng thái chết của Samus

	int immortal_time;
	bool isImmortal;
	float jumdistance;
	bool isOnGround;
	bool isCrouching;

	Samus();
	Samus(LPD3DXSPRITE spriteHandler, World * manager);
	~Samus();
	//DirectCollision getDirection();
	//void setDirection(DirectCollision direction);

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void InitPostition();

	SAMUS_STATE GetState();
	void SetState(SAMUS_STATE value);

	void ResetAllSprites();
	bool isSamusCrouch();
	bool isSamusDeath();
	bool GetStateActive();
	void setListBullet(BulletObject ** listbullet)
	{
		this->listBullet = listbullet;
	}
	BulletObject ** getlistbullet()
	{
		return this->listBullet;
	}
	int getNumBullet()
	{
		return num;
	}
	void setNum(int num)
	{
		this->num = num;
	}

	bool Samus::isSamusOnGround()
	{
		return isOnGround;
	}
	bool isSamusImmortal();
	void setSamusImmortal(bool result);
	float getImmortalTime();
	void setImmortalTime(float time);

	void _Shoot(BULLET_DIRECTION dir, Metroid*);
	void _SetBoom(BULLET_DIRECTION dir, Metroid*);
	void _SetBoom(BULLET_DIRECTION dir, Metroid * metroid, float pos_x, float pos_y);

	void _ShootMissile(BULLET_DIRECTION dir, Metroid*);
	void SetMissileNumbers(int value);
	int GetMissileNumbers();
	int GetBoomNumbers();
	void SetBoomNumbers(int num);

	//================ OVERRIDE VIRTUAL METHOD ==================
	void Reset(int  x, int y);
	void Update(float t);
	void Render();
	void Destroy();
	void SetHealth(float value);
	float GetHealth();
	void TakeDamage(float damage);

	void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta, Metroid*);
	void OnkeyDown(int KeyCode, Metroid*, int&);
	void OnKeyUp(int KeyCode, Metroid* metroid);

	void Response(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	void SlideFromGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	void Deflect(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	//================= END OVERRIDE VIRTUAL METHOD =============
};
#endif // !_SAMUS_H