#pragma once
#include "Item.h"
#include "Parameters.h"

class MissileItem : public Item
{
public:
	MissileItem(LPD3DXSPRITE spriteHandler, World * manager);
	~MissileItem();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Destroy();
};

