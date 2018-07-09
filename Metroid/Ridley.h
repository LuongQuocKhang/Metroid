#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include "Parameters.h"

#define RIDLEY_ANIMATE_RATE 2

class Ridley : public Enemy
{
protected:
	World * manager;
	Sprite * fly;
	float time_push; //thời gian push lực y cho Ridley bay lên
public:
	Ridley(LPD3DXSPRITE spriteHandler, World * manager);
	~Ridley();

	//============= OVERRIDE VIRTUAL METHOD ==================
	void Update(float t);
	void Render();
	//============= END OVERRIDE VIRTUAL METHOD ==============
};