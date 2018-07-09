#pragma once
#include "Item.h"
#include "Parameters.h"
class MorphItem : public Item
{
public:
	MorphItem(LPD3DXSPRITE spriteHandler, World * manager);
	~MorphItem();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Update(float t);
	void Render();
	void Destroy();
};

