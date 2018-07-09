#include "SentryBullet.h"
#include "World.h"
#include "GroupObject.h"


SentryBullet::SentryBullet(World * manager)
{
	this->manager = manager;
	up = NULL;
	left = NULL;
	right = NULL;
	bottom = NULL;
	topleft = NULL;
	topright = NULL;
	bottomleft = NULL;
	bottomright = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;

	damage = DAMAGE_SENTRY_BULLET;

	this->bulletType = SENTRY_BULLET;

	//Set collider
	collider = new Collider(0, 0, -SENTRY_BULLET_HEIGHT, SENTRY_BULLET_WIDTH);
}

SentryBullet::~SentryBullet()
{
}

void SentryBullet::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	up = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_UP, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
	left = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_LEFT, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
	right = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_RIGHT, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
	bottom = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_BOTTOM, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
	topleft = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_TOPLEFT, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
	topright = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_TOPRIGHT, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
	bottomleft = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_BOTTOMLEFT, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
	bottomright = new Sprite(_SpriteHandler, SENTRY_BULLET_SPIRTE_PATH, SENTRY_BULLET_BOTTOMRIGHT, SENTRY_BULLET_WIDTH, SENTRY_BULLET_HEIGHT, SENTRY_BULLET_SPRITE_COUNT, SPRITE_PER_ROW);
}

void SentryBullet::Update(float t)
{
	if (!isActive)
		return;

	// Va chạm của Sentry_Bullet đối với Samus
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
	case ON_LEFT:
		isActive = true;
		vx = -SPEED;
		vy = 0;
		break;
	case ON_RIGHT:
		isActive = true;
		vx = SPEED;
		vy = 0;
		break;
	case ON_UP:
		isActive = true;
		vy = SPEED;
		vx = 0;
		break;
	case ON_BOTTOM:
		isActive = true;
		vy = -SPEED;
		vx = 0;
		break;
	case ON_TOPLEFT:
		isActive = true;
		vy = SPEED;
		vx = -SPEED;
		break;
	case ON_TOPRIGHT:
		isActive = true;
		vy = SPEED;
		vx = SPEED;
		break;
	case ON_BOTTOMLEFT:
		isActive = true;
		vy = -SPEED;
		vx = -SPEED;
		break;
	case ON_BOTTOMRIGHT:
		isActive = true;
		vy = -SPEED;
		vx = SPEED;
		break;
	case NONE:
		isActive = false;
		vx = 0;
		vy = 0;
		break;
	}

	pos_x += vx*t;
	pos_y += vy*t;

	//int temp_x = vx*t;
	//int temp_y = vy*t;

	//if (temp_x < 0)
	//	temp_x = -temp_x;
	//if (temp_y < 0)
	//	temp_y = -temp_y;

	//limit_dist_x += temp_x;
	//limit_dist_y += temp_y;


	////Check if the bullet reach the limit
	//if (limit_dist_x >= LIMIT_DISTANCE || limit_dist_y >= LIMIT_DISTANCE)
	//{
	//	Reset();
	//}
}

void SentryBullet::Render()
{
	if (isActive)
	{
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		switch (direction)
		{
		case ON_LEFT:
			left->Render(pos_x, pos_y);
			break;
		case ON_RIGHT:
			right->Render(pos_x, pos_y);
			break;
		case ON_UP:
			up->Render(pos_x, pos_y);
			break;
		case ON_BOTTOM:
			bottom->Render(pos_x, pos_y);
			break;
		case ON_TOPLEFT:
			topleft->Render(pos_x, pos_y);
			break;
		case ON_TOPRIGHT:
			topright->Render(pos_x, pos_y);
			break;
		case ON_BOTTOMLEFT:
			bottomleft->Render(pos_x, pos_y);
			break;
		case ON_BOTTOMRIGHT:
			bottomright->Render(pos_x, pos_y);
			break;
		}
		_SpriteHandler->End();
	}
}

void SentryBullet::Shoot(BULLET_DIRECTION dir, float posX, float posY)
{
	direction = dir;	//cái này xem như set active
	isActive = true;
	pos_x = posX;
	pos_y = posY;
}
