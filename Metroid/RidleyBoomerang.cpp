#include "RidleyBoomerang.h"
#include "World.h"
#include "GroupObject.h"

#define LIMIT_DISTANCE_BOOMERANG 500

RidleyBoomerang::RidleyBoomerang(World * manager)
{
	this->manager = manager;
	right = NULL;

	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;

	damage = DAMAGE_RIDLEY_BOOMERANG;

	this->bulletType = BOOMERANG;
	//Set collider
	collider = new Collider(0, 0, -RIDLEY_BOOMERANG_HEIGHT, RIDLEY_BOOMERANG_WIDTH);
}

RidleyBoomerang::~RidleyBoomerang()
{
	delete(right);
}

void RidleyBoomerang::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	right = new Sprite(_SpriteHandler, RIDLEY_BOOMERANG_SPIRTE_PATH, RIDLEY_BOOMERANG_PATH, RIDLEY_BOOMERANG_WIDTH, RIDLEY_BOOMERANG_HEIGHT, RIDLEY_BOOMERANG_SPRITE_COUNT, SPRITE_PER_ROW);

}

void RidleyBoomerang::Update(float t)
{
	//if (!IsInCamera())
	//	Reset();

	if (!isActive)
		return;

	vy -= 0.1f;

	// Va chạm của Ridley_Boomerang đối với Samus
	float TimeScale = SweptAABB(manager->samus, t);
	if (TimeScale < 1.0f)
	{
		manager->samus->TakeDamage(this->damage);
		//Reset();
	}

	// Xử lý va chạm
	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				Reset();
			}
			break;
		}
	}

	for (int i = 0; i < manager->colBrick->size; i++)
	{
		float timeScale = SweptAABB(manager->colBrick->objects[i], t);
		if (timeScale < 1.0f)
			Reset();
	}

	//
	// Update bullet status
	//
	switch (direction)
	{
	case ON_RIGHT:
		isActive = true;
		vx = RIDLEY_BULLET_SPEED;
		break;
	case NONE:
		isActive = false;
		vx = 0;
		vy = 0;
		break;
	}

	time_push -= t;
	if (time_push <= 0)
	{
		vy -= 0.1f;
	}
	else
	{
		vy += BULLET_PUSH_VELOCITY_Y;
	}

	pos_x += vx * t;
	pos_y += vy * t;

	//int temp_x = vx * t;
	//int temp_y = vy * t;

	//if (temp_x < 0)
	//	temp_x = -temp_x;
	//if (temp_y < 0)
	//	temp_y = -temp_y;

	//limit_dist_x += temp_x;
	//limit_dist_y += temp_y;


	////Check if the bullet reach the limit
	//if (limit_dist_x >= LIMIT_DISTANCE_BOOMERANG || limit_dist_y >= LIMIT_DISTANCE_BOOMERANG)
	//{
	//	Reset();
	//}
}

void RidleyBoomerang::Render()
{
	if (isActive)
	{
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		switch (direction)
		{
		case ON_RIGHT:
			right->Render(pos_x, pos_y);
			break;
		}
		_SpriteHandler->End();
	}
}

void RidleyBoomerang::Shoot(BULLET_DIRECTION dir, float posX, float posY)
{
	direction = dir;	//cái này xem như set active
	isActive = true;
	pos_x = posX;
	pos_y = posY;
	time_push = RIDLEY_BOOMERANG_TIME_PUSH;
}

void RidleyBoomerang::Reset()
{
	//Ngung render
	isActive = false;

	//Reset vi tri
	ResetPosition();

	//Reset distance
	limit_dist_x = 0;
	limit_dist_y = 0;

	//Set direction to NONE
	direction = NONE;

	time_push = RIDLEY_BOOMERANG_TIME_PUSH;
}
