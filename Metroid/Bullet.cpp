#include "Bullet.h"
#include "World.h"
#include "GroupObject.h"


void Bullet::Render()
{
	if (isActive)
	{
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		bullet->Render(pos_x, pos_y + 12);
		_SpriteHandler->End();
	}
}

Bullet::Bullet(World * manager)
{
	bullet = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;

	this->bulletType = STANDARD;
	this->manager = manager;
	collider = new Collider(0, 0, -BULLET_HEIGHT, BULLET_WIDTH);
}

Bullet::Bullet(World * manager, int x_holder, int y_holder)
{
	bullet = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;

	damage = DAMAGE_SAMUS_BULLET;
	this->bulletType = STANDARD;
	pos_x_holder = x_holder;
	pos_y_holder = y_holder;
	collider = new Collider(0, 0, -BULLET_HEIGHT, BULLET_WIDTH);
}


Bullet::~Bullet()
{
	delete(bullet);
}

void Bullet::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	bullet = new Sprite(_SpriteHandler, BULLET_SPRITE_PATH, BULLET_SPRITE, BULLET_WIDTH, BULLET_HEIGHT, BULLET_COUNT, SPRITE_PER_ROW);

	//Set collider
	collider = new Collider(0, 0, -BULLET_HEIGHT, BULLET_WIDTH);
}

void Bullet::Update(float t)
{
	if (!isActive)
		return;

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
						hog_yellow->TakeDamage(this->damage); break;
					}
				}
				break;
				case BEDGEHOG_PINK:
				{
					Bedgehog * hog_pink = (Bedgehog*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
						hog_pink->TakeDamage(this->damage); break;
					}
				}

				break;
				case BIRD:
				{
					Bird * bird = (Bird*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
						bird->TakeDamage(this->damage); break;
					}
				}
				break;
				case BEE:
				{
					Bee * bee = (Bee*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
						bee->TakeDamage(this->damage); break;
					
					}
				}
				break;
				case RIDLEY:
				{
					Ridley * ridley = (Ridley*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
						ridley->TakeDamage(this->damage); break;
					}
				}
				break;
				case MOTHER_BRAIN:
				{
					MotherBrain * motherBrain = (MotherBrain*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{
						motherBrain->TakeDamage(this->damage); break;
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

	//Xử lý va chạm với gate
	for (int i = 0; i < manager->otherGO->size; i++)
	{
		float timeScale = SweptAABB(manager->otherGO->objects[i], t);
		if (timeScale < 1.0f)
		{
			switch (manager->otherGO->objects[i]->GetType())
			{
			case GATE:
			{
				Gate * gate = (Gate*)manager->otherGO->objects[i];
				gate->DestroyGate();
				break;
			}
			}
		}
	}
	

	// Va chạm của Bird_bullet đối với samus
	float TimeScale = SweptAABB(manager->samus, t);
	if (TimeScale < 1.0f)
	{
		manager->samus->TakeDamage(this->damage);
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

	int temp_x = vx*t;
	int temp_y = vy*t;

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
}

