#include "Block.h"
#include "World.h"
#include "GroupObject.h"

Block::Block()
{
}

Block::Block(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->enemy_type = enemy_type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	//Khởi tạo máu
	health = HEALTH_BLOCK;

	//Khởi tạo sát thương
	damage = DAMAGE_BLOCK;

	//Set collider
	collider = new Collider();
	collider->SetCollider(BLOCK_HEIGHT / 2, -BLOCK_WIDTH / 2, -BLOCK_HEIGHT / 2, BLOCK_WIDTH / 2);

	vy = 0;
	vx = BLOCK_SPEED;
}


Block::~Block()
{
	delete(left);
	delete(right);
}

void Block::InitSprites()
{

	char  *left_path = NULL, *right_path = NULL;
	switch (enemy_type)
	{
	case BLOCK:
		left_path = BLOCK_LEFT;
		right_path = BLOCK_RIGHT;
		break;
	}

	// Khởi tạo sprite
	left = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, left_path, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_SPRITE_COUNT, 1);
	right = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, right_path, BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_SPRITE_COUNT, 1);
}

void Block::Update(float t)
{
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	// Xét va chạm, nếu va chạm thì đi ngược lại
	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			// Nếu có va chạm
			if (timeScale < 1.0f)
			{
				// Đổi hướng di chuyển
				vx = -vx;
			}
			break;
		}
		
	}

	for (int i = 0; i < manager->colBrick->objects.size(); i++)
	{
		float timeScale = SweptAABB(manager->colBrick->objects[i], t);
		// Nếu có va chạm
		if (timeScale < 1.0f)
		{
			// Đổi hướng di chuyển
			vx = -vx;
		}
	}

	pos_x += vx*t;
	pos_y += vy*t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case ON_BLOCK_LEFT:
			left->Next();
			break;
		case ON_BLOCK_RIGHT:
			right->Next();
			break;
		}
		last_time = now;
	}

	// --TO DO: Xử lý va chạm
	// ...
	// Khi cần xử lý va chạm, gọi groupCollision ở world
	//	
}

void Block::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (state)
	{
	case ON_BLOCK_LEFT:
		left->Render(pos_x, pos_y);
		break;
	case ON_BLOCK_RIGHT:
		right->Render(pos_x, pos_y);
		break;
	}
	spriteHandler->End();
}
