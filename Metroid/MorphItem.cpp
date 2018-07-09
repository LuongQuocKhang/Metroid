#include "MorphItem.h"
#include "World.h"
#include "GroupObject.h"

MorphItem::MorphItem(LPD3DXSPRITE spriteHandler, World * manager) :Item(spriteHandler, manager)
{
	item_type = MORPH_BALL_ITEM;
	// Set collider
	collider = new Collider(0, 0, -ITEM_MORPH_BALL_HEIGHT, ITEM_MORPH_BALL_WIDTH);

	isActive = true;
}

MorphItem::~MorphItem()
{
}

void MorphItem::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Item::InitSprites(d3ddv);
	itemSprite = new Sprite(spriteHandler, ITEM_SPRITE_PATH, ITEM_MORPH_BALL, ITEM_MORPH_BALL_WIDTH, ITEM_MORPH_BALL_HEIGHT, ITEM_MORPH_BALL_COUNT, 1);
}

void MorphItem::Update(float t)
{
	//if (!isActive)
	//	return;

	//vy -= FALLDOWN_VELOCITY_DECREASE;


	//// Xét va chạm với ground
	//for (int i = 0; i < manager->quadtreeGroup->size; i++)
	//{
	//	switch (manager->quadtreeGroup->objects[i]->GetType())
	//	{
	//	case BRICK:
	//		float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);

	//		// Chỉ cần xét va chạm phía trên cục gạch thôi
	//		if (timeScale < 1.0f && normaly > 0.1f)
	//		{
	//			this->pos_y = (manager->quadtreeGroup->objects[i]->GetPosY() + manager->quadtreeGroup->objects[i]->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
	//			pos_y -= vy*t;
	//		}
	//		break;
	//	}
	//}

	//pos_x += vx*t;
	//pos_y += vy*t;

	// Morph ball không cần set thời gian để biến mất như những item khác
	// xxx
}

void MorphItem::Render()
{
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	itemSprite->Render(pos_x, pos_y);
	spriteHandler->End();
}

void MorphItem::Destroy()
{
	isActive = false;
}


