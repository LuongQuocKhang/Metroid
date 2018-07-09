#pragma once
#ifndef _Number_H_
#define _Number_H_

#include "GameObject.h"
#include "Parameters.h"
enum NUMBER_TYPE //Chia type number ra 2 loại là energy và missile
{
	NUMBEROFENERGY,
	NUMBEROFMISSILE
};
enum NUMBER_PATH_TYPE   //Chia type path number ra 2 loại chục và đơn vị
{
	CHUC,
	DONVI
};
class Number : public GameObject
{
protected:
	Sprite * number1; //Số chục
	Sprite * number2; //Số đơn vị
	int health;
	NUMBER_PATH_TYPE numberpath;
	NUMBER_TYPE numbertype;
public:
	Number();
	Number(LPD3DXSPRITE spriteHandler, World * manager, NUMBER_PATH_TYPE number_path, NUMBER_TYPE number_type);
	~Number();

	void InitSprites();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(int t);
	virtual void Render();
	void SetHealth(int value); //Set giá trị Health
	int GetHealth();
	void Check_DV(int n);//Dùng để lấy số đơn vị
	void Check_C(int n);//Dùng để lấy số chục
						//============== END OVERRIDE VIRTUAL METHOD ===============
};

#endif // !_Number_H_