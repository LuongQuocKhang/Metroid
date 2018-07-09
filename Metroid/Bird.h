#pragma once
#ifndef _Bird_H_
#define _Bird_H_

#include "Enemy.h"
#include "Parameters.h"

class Bird : public Enemy
{
protected:
	Sprite * fly;

	Collider * collider_area;

	int animate_rate;	// cần biến này vì khi dí theo Samus animate rate thay đổi
public:
	Bird();
	Bird(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type);
	~Bird();

	void InitSprites();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
	bool IsCollide(GameObject* target);
	void Response(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	void Destroy();
};

#endif // !_Bird_H_
