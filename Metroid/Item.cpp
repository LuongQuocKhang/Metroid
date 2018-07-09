#include "Item.h"
#include "World.h"
#include "GroupObject.h"

Item::Item(LPD3DXSPRITE sprietHandler, World * manager)
{
	this->type = ITEM;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->time_survive = ITEM_TIME_SURVIVE;

	vx = 0;
	vy = 0;
}

Item::~Item()
{
	delete(itemSprite);
}

int Item::getNumberGain()
{
	return number_gain;
}

void Item::setNumberGain(int num)
{
	number_gain = num;
}

void Item::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
}

void Item::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	time_survive = ITEM_TIME_SURVIVE;
}



void Item::Update(int t)
{
	if (!isActive)
		return;

	//vy -= 0.005f*t;
	//vy -= GRAVITY_VELOCITY*t;
	

	// Xét va chạm với ground
	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);

			// Chỉ cần xét va chạm phía trên cục gạch thôi
			if (timeScale < 1.0f && normaly > 0.1f)
			{
				this->pos_y = (manager->quadtreeGroup->objects[i]->GetPosY() + manager->quadtreeGroup->objects[i]->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
				pos_y -= vy*t;
			}
			break;
		}
	}

	pos_x += vx*t;
	pos_y += vy*t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		itemSprite->Next();
		last_time = now;
	}

	// Tính thời gian hiển thị
	time_survive -= t;
	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		isActive = false;
	}
}

void Item::Render()
{
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	itemSprite->Render(pos_x, pos_y);
	spriteHandler->End();
}
