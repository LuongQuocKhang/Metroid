#include "BulletObject.h"
#include "World.h"
#include "GroupObject.h"


BulletObject::BulletObject()
{
}

BulletObject::BulletObject(World * manager)
{
	this->manager = manager;
}

BulletObject::~BulletObject()
{
}

void BulletObject::InitPosition(int posX, int posY)
{
	pos_x = posX;
	pos_y = posY;

	pos_x_holder = posX;
	pos_y_holder = posY;

	direction = NONE;
}

void BulletObject::ResetPosition()
{
	pos_x = pos_x_holder;
	pos_y = pos_y_holder;
}

void BulletObject::Reset()
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
}

BULLET_DIRECTION BulletObject::GetDirection()
{
	return direction;
}

void BulletObject::SetDirection(BULLET_DIRECTION value)
{
	direction = value;
}

void BulletObject::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
}

void BulletObject::Update(float t)
{
	if (!isActive)
		return;

	//// Đạn va chạm với samus	====>	Không dùng được ========> Xét từng TH riêng cho mỗi loại đạn trong class con
	//if (manager->samus->GetStateActive())
	//{
	//	float timeScale = SweptAABB(manager->samus, t);
	//	if (timeScale < 1.0f)
	//	{
	//		switch (getBulletType())
	//		{
	//		case BIRD_BULLET:
	//			manager->samus->TakeDamage(this->damage);
	//		case BOOMERANG:
	//			manager->samus->TakeDamage(this->damage);
	//		case SENTRY_BULLET:
	//			manager->samus->TakeDamage(this->damage);
	//		}
	//	}
	//}

	// Đạn samus va chạm với Enemy (Hiện chỉ có Missile của samus là tác dụng va chạm dc tới enemy)
	for (int i = 0; i < manager->enemyGroup->size; i++)
	{
		if (manager->enemyGroup->objects[i]->IsActive())
		{
			float timeScale = SweptAABB(manager->enemyGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				manager->enemyGroup->objects[i]->isHit = true;
				switch (manager->enemyGroup->objects[i]->GetType())
				{
				case BEDGEHOG_YELLOW:
				{
					Bedgehog * hog_yellow = (Bedgehog*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
					case STANDARD:	hog_yellow->TakeDamage(this->damage); break;
					case MISSILE:	hog_yellow->TakeDamage(this->damage); break;
					}
				}
				break;
				case BEDGEHOG_PINK:
				{
					Bedgehog * hog_pink = (Bedgehog*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
					case STANDARD:	hog_pink->TakeDamage(this->damage); break;
					case MISSILE:	hog_pink->TakeDamage(this->damage); break;
					}
				}

				break;
				case BIRD:
				{
					Bird * bird = (Bird*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
					case STANDARD:	bird->TakeDamage(this->damage); break;
					case MISSILE:	bird->TakeDamage(this->damage); break;
					}
				}
				break;
				case BEE:
				{
					Bee * bee = (Bee*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
					case STANDARD:	bee->TakeDamage(this->damage); break;
					case MISSILE:	bee->TakeDamage(this->damage); break;
					}
				}
				break;
				case RIDLEY:
				{
					Ridley * ridley = (Ridley*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
					case STANDARD:	ridley->TakeDamage(this->damage); break;
					case MISSILE:	ridley->TakeDamage(this->damage); break;
					}
				}
				break;
				case MOTHER_BRAIN:
				{
					MotherBrain * motherBrain = (MotherBrain*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
					case STANDARD:	motherBrain->TakeDamage(this->damage); break;
					case MISSILE:	motherBrain->TakeDamage(this->damage); break;
					}
				}
				break;
				case BLOCK:
					break;
				}
				Reset();
			}
		}
	}
	//<======================

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
	case NONE:
		isActive = false;
		vx = 0;
		vy = 0;
		break;
	}

	pos_x += vx * t;
	pos_y += vy * t;

	int temp_x = vx * t;
	int temp_y = vy * t;

	if (temp_x < 0)
		temp_x = -temp_x;
	if (temp_y < 0)
		temp_y = -temp_y;

	limit_dist_x += temp_x;
	limit_dist_y += temp_y;


	//Check if the bullet reach the limit
	if (limit_dist_x >= LIMIT_DISTANCE || limit_dist_y >= LIMIT_DISTANCE)
	{
		Reset();
	}

	//Update position of samus
	//pos_x_holder = posX;
	//pos_y_holder = posY;
}

void BulletObject::Render()
{

}

void BulletObject::Shoot(BULLET_DIRECTION dir)
{
	direction = dir;	//cái này xem như set active
	isActive = true;
	pos_x = pos_x_holder;
	pos_y = pos_y_holder;
}

void BulletObject::Shoot(BULLET_DIRECTION dir, float posX, float posY)
{
	direction = dir;	//cái này xem như set active
	isActive = true;
	pos_x = posX;
	pos_y = posY;
}
