#include "Ridley.h"
#include "World.h"
#include "GroupObject.h"
#include "BulletManager.h"

Ridley::Ridley(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->enemy_type = RIDLEY;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = true;

	health = HEALTH_RIDLEY;

	fly = new Sprite(spriteHandler, BOSS_SPRITE_PATH, RIDLEY_FLY_PATH, RIDLEY_WIDTH, RIDLEY_HEIGHT, RIDLEY_SPRITE_COUNT, SPRITE_PER_ROW);

	//--TO DO: Khởi tạo collider cho Ridley
	collider = new Collider();
	collider->SetCollider(RIDLEY_HEIGHT / 2, -RIDLEY_WIDTH / 2, -RIDLEY_HEIGHT / 2 - 10, RIDLEY_WIDTH / 2);
}

Ridley::~Ridley()
{
	delete(fly);
}

void Ridley::Update(float t)
{
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				//SlideFromGround(manager->quadtreeGroup->objects[i], t, timeScale);
				time_push = 300;
				vy = 0;
			}
			break;
		}
	}

	for (int i = 0; i < manager->colFloorBrick->size; i++)
	{
		float timeScale = SweptAABB(manager->colFloorBrick->objects[i], t);
		if (timeScale < 1.0f)
		{
			SlideFromGround(manager->colFloorBrick->objects[i], t, timeScale);
			time_push = 300;
			vy = 0;
		}
	}

	time_push -= t;
	if (time_push <= 0)
	{
		vy -= 0.007f;
	}
	else
	{
		vy += 0.011f;
	}

	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / RIDLEY_ANIMATE_RATE)
	{
		manager->ridleyBoomerang->Next(ON_RIGHT, pos_x, pos_y);
		fly->Next();
		last_time = now;
	}

	// --TO DO: Xử lý va chạm
	// ...
	// Khi cần xử lý va chạm, gọi groupCollision ở world
	//	
}

void Ridley::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	fly->Render(pos_x, pos_y);
	spriteHandler->End();
}
