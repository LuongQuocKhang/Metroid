#include "Brick.h"



Brick::Brick()
{
}

Brick::Brick(LPD3DXSPRITE spriteHandler, World * manager, BRICK_TYPE type, int id, int posX, int posY)
{
	this->type = BRICK;

	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->brick_type = type;
	this->id = id;
	this->pos_x = posX;
	this->pos_y = posY;
	this->isPassable = false;
	this->isActive = true;
	
	//lấy ra số lượng sprite theo width và height, đường dẫn đến sprite tùy vào loại gạch nào
	switch (type)
	{
	case GROUND:
		width_count = BRICK_1_WIDTH_COUNT;
		height_count = BRICK_1_HEIGHT_COUNT;
		sprite_path = BRICK_1_PATH;
		break;
	case FLOOR:
		width_count = BRICK_2_WIDTH_COUNT;
		height_count = BRICK_2_HEIGHT_COUNT;
		sprite_path = BRICK_2_PATH;
		break;
	case ALL:
		width_count = BRICK_WIDTH_COUNT;
		height_count = BRICK_HEIGHT_COUNT;
		sprite_path = BRICK_PATH;
	}

	// đặt vx và vy bằng 0 (vì là gameobject tĩnh)
	vx = 0;
	vy = 0;

	this->InitSprite();

	//--TO DO: Set collider cho brick

	collider = new Collider();
	collider->SetCollider(0, 0, -BRICK_HEIGHT, BRICK_WIDTH);
}


Brick::~Brick()
{
}

void Brick::InitSprite()
{
	//Tính index của viên gạch
	int index_x = id % width_count;
	int index_y = id / width_count;

	//Lấy index nhân với kích thước -> ra được vị trí
	//Lưu ý: đây là vị trí để cắt sprite chứ không phải vị trí của Brick trên Game
	//Vị trí của Brick trên game sẽ tính sau
	int x = index_x * BRICK_WIDTH;		
	int y = index_y * BRICK_HEIGHT;
	
	sprite = new Sprite(spriteHandler, sprite_path, x, y, BRICK_WIDTH, BRICK_HEIGHT);
}

int Brick::GetId()
{
	return id;
}

void Brick::SetId(int id)
{
	this->id = id;
}

BRICK_TYPE Brick::GetBrickType()
{
	return brick_type;
}

void Brick::SetPassable(bool value)
{
	isPassable = value;
}

bool Brick::IsPassable()
{
	return isPassable;
}

void Brick::Update(float t)
{
	
}

void Brick::Render()
{
	// Không cần phải xét isActive mới lấy chi cho mệt, vì Brick này do quadtree quản lý
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Render(pos_x, pos_y);
	spriteHandler->End();
}
