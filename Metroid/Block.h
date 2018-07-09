#pragma once
#ifndef _Block_H_
#define _Block_H_

#include "Enemy.h"
#include "Parameters.h"

enum BLOCK_STATE
{
	ON_BLOCK_LEFT,
	ON_BLOCK_RIGHT
};

class Block : public Enemy
{
protected:
	BLOCK_STATE state;
	Sprite * left;
	Sprite * right;

public:
	Block();
	Block(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type);
	~Block();

	void InitSprites();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============
};

#endif // !_Block_H_
