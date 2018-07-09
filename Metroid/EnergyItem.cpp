#include "EnergyItem.h"


EnergyItem::EnergyItem(LPD3DXSPRITE spriteHandler, World * manager):Item(spriteHandler, manager)
{
	item_type = ENERGY_ITEM;
	number_gain = ITEM_ENERGY_HEALTH_GAIN;
	//Set collider
	collider = new Collider(0, 0, -(ITEM_ENERGY_HEIGHT + 5.0f), ITEM_ENERGY_WIDTH);
}

EnergyItem::~EnergyItem()
{
}

void EnergyItem::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Item::InitSprites(d3ddv);
	itemSprite = new Sprite(spriteHandler, ITEM_SPRITE_PATH, ITEM_ENERGY, ITEM_ENERGY_WIDTH, ITEM_ENERGY_HEIGHT, ITEM_ENERGY_COUNT, 1);
}

void EnergyItem::Destroy()
{
	this->isActive = false;
}