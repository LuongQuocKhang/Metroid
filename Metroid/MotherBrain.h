#pragma once
#include "GameObject.h"
#include "Parameters.h"
#include "Enemy.h"

class MotherBrain : public Enemy
{
protected:
	World * manager;

	Sprite * unbroken;
	Sprite * broken;
	MOTHERBRAIN_STATE state;
public:
	MotherBrain(LPD3DXSPRITE spriteHandler, World * manager);
	~MotherBrain();

	//============= OVERRIDE VIRTUAL METHOD ==================
	void Update(float t);
	void Render();
	//============= END OVERRIDE VIRTUAL METHOD ==============
	void Destroy();
};