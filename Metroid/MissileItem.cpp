#include "MissileItem.h"


MissileItem::MissileItem(LPD3DXSPRITE spriteHandler, World * manager) : Item(spriteHandler, manager)
{
	item_type = MISSILE_ITEM;
	number_gain = ITEM_MISSILE_GAIN;
	//Set collider
	collider = new Collider(0, 0, -(ITEM_MISSILE_HEIGHT + 5.0f), ITEM_MISSILE_WIDTH);
}

MissileItem::~MissileItem()
{
}

void MissileItem::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Item::InitSprites(d3ddv);
	itemSprite = new Sprite(spriteHandler, ITEM_SPRITE_PATH, ITEM_MISSILE, ITEM_MISSILE_WIDTH, ITEM_MISSILE_HEIGHT, ITEM_MISSILE_COUNT, 1);
}

void MissileItem::Destroy()
{
	isActive = false;
}
