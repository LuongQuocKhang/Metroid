#pragma once
#ifndef _Bee_H_
#define _Bee_H_

#include "Enemy.h"
#include "Parameters.h"

class Bee : public Enemy
{
protected:
	Sprite * fly;
	Collider * collider_area;
	float time_push;
public:
	Bee(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type);
	~Bee();

	void InitSprites();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
	bool IsCollide(GameObject* target);
	void Destroy();
};

#endif // !_Bee_H_
