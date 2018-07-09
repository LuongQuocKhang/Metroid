#include "BirdBullet.h"
#include "World.h"
#include "GroupObject.h"
#include "Bullet.h"


BirdBullet::BirdBullet(World * manager)
{
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;	

	//damage = DAMAGE_BIRD_BULLET;

	for (int i = 0; i < BIRD_BULLET_COUNT; i++)
	{
		bullets[i] = new Bullet(this->manager);
		bullets[i]->damage = DAMAGE_BIRD_BULLET;
		this->bulletType = BIRD_BULLET;
	}
}


BirdBullet::~BirdBullet()
{
}

void BirdBullet::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	for (int i = 0; i < BIRD_BULLET_COUNT; i++)
	{
		bullets[i]->InitSprites(d3ddv);
	}
}

void BirdBullet::Update(float t)
{
	if (!isActive)
		return;

	for (int i = 0; i < BIRD_BULLET_COUNT; i++)
	{
		float TimeScale = bullets[i]->SweptAABB(manager->samus, t);
		if (TimeScale < 1.0f)
		{
			manager->samus->TakeDamage(this->damage);
		}
	}

	for (int i = 0; i < BIRD_BULLET_COUNT; i++)
	{
		bullets[i]->Update(t);
	}
}

void BirdBullet::Render()
{
	for (int i = 0; i < BIRD_BULLET_COUNT; i++)
	{
		bullets[i]->Render();
	}
}

void BirdBullet::Shoot(BULLET_DIRECTION dir, float posX, float posY)
{
	bullets[0]->Shoot(BULLET_DIRECTION::ON_LEFT, posX, posY);
	bullets[1]->Shoot(BULLET_DIRECTION::ON_TOPLEFT, posX, posY);
	bullets[2]->Shoot(BULLET_DIRECTION::ON_UP, posX, posY);
	bullets[3]->Shoot(BULLET_DIRECTION::ON_TOPRIGHT, posX, posY);
	bullets[4]->Shoot(BULLET_DIRECTION::ON_RIGHT, posX, posY);

	isActive = true;

	pos_x = posX;
	pos_y = posY;
}
