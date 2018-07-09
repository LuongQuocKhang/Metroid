#pragma once
#ifndef _Energy_H_
#define _Energy_H_

#include "GameObject.h"
#include "Parameters.h"
enum TYPE //Chia type ra 2 loại là Energyinfo và missileinfo
{
	ENERGYINFO,
	MISSILEINFO
};
class Energy : public GameObject
{
protected:
	Sprite * energy;
	TYPE type;
public:
	Energy();
	Energy(LPD3DXSPRITE spriteHandler, World * manager, TYPE type);
	~Energy();

	void InitSprites();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(int t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
};

#endif // !_Energy_H_