#pragma once
#include "Item.h"
class EnergyItem : public Item
{
public:
	EnergyItem(LPD3DXSPRITE spriteHandler, World * manager);
	~EnergyItem();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Destroy();
};

