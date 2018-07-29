#include "RidleyBoomerang.h"
#include "World.h"
#include "GroupObject.h"

#define LIMIT_DISTANCE_BOOMERANG 500

RidleyBoomerang::RidleyBoomerang(LPD3DXSPRITE spriteHandler,World * manager)
{
	this->manager = manager;
	right = NULL;
	this->spriteHandler = spriteHandler;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;

	damage = DAMAGE_RIDLEY_BOOMERANG;

	this->bulletType = BOOMERANG;
	//Set collider
	collider = new Collider(RIDLEY_BOOMERANG_HEIGHT / 2, -RIDLEY_BOOMERANG_WIDTH / 2, -RIDLEY_BOOMERANG_HEIGHT / 2, RIDLEY_BOOMERANG_WIDTH / 2);
}

RidleyBoomerang::~RidleyBoomerang()
{
	delete(right);
}

void RidleyBoomerang::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	right = new Sprite(spriteHandler, RIDLEY_BOOMERANG_SPIRTE_PATH, RIDLEY_BOOMERANG_PATH, RIDLEY_BOOMERANG_WIDTH, RIDLEY_BOOMERANG_HEIGHT, RIDLEY_BOOMERANG_SPRITE_COUNT, SPRITE_PER_ROW);

}
void RidleyBoomerang::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 image)
{
	//Create sprite
	right = new Sprite(spriteHandler, image, RIDLEY_BOOMERANG_PATH, RIDLEY_BOOMERANG_WIDTH, RIDLEY_BOOMERANG_HEIGHT, RIDLEY_BOOMERANG_SPRITE_COUNT, SPRITE_PER_ROW);
}

void RidleyBoomerang::Update(float t)
{
	//if (!IsInCamera())
	//	Reset();

	if (!isActive)
		return;

	vy -= 0.1f;
	// Xử lý va chạm
	for (int i = 0; i < manager->colFloorBrick->size; i++)
	{
		float timeScale = SweptAABB(manager->colFloorBrick->objects[i], t);
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
}

void RidleyBoomerang::Render()
{
	if (isActive)
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		switch (direction)
		{
		case ON_RIGHT:
			right->Render(pos_x, pos_y);
			break;
		}
		spriteHandler->End();
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
