#include "Bird.h"
#include "World.h"
#include "GroupObject.h"
#include "Parameters.h"
#include "Metroid.h"
#include "ColliderBrick.h"

Bird::Bird()
{
}

Bird::Bird(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->isHit = false;
	this->enemy_type = enemy_type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	//Khởi tạo máu
	health = HEALTH_BIRD;

	//Khởi tạo sát thương
	damage = DAMAGE_BIRD;

	width = BIRD_WIDTH;
	height = BIRD_HEIGHT;

	//Set animate rate ban đầu
	animate_rate = BIRD_STANDARD_ANIMATE_RATE;

	//Set collider
	collider = new Collider();
	collider->SetCollider(BIRD_HEIGHT / 2, -BIRD_WIDTH / 2, -BIRD_HEIGHT / 2, BIRD_WIDTH / 2);

	// collider dùng khi samus đi vào vùng va chạm
	collider_area = new Collider();
	collider_area->SetCollider(0, -width, -480, width * 2);
}


Bird::~Bird()
{
	delete(fly);
}

void Bird::InitSprites()
{
	char  *fly_path = NULL;
	switch (enemy_type)
	{
	case BIRD:
		fly_path = BIRD_FLY;
		break;
	}

	// Khởi tạo sprite
	fly = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, fly_path, BIRD_WIDTH, BIRD_HEIGHT, BIRD_FLY_SPRITE_COUNT, 1);
}
void Bird::Update(float t)
{
	if (!isActive) return;

	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		return;
	}
	// khi samus đi vào vùng va chạm

	if (this->IsCollide(manager->samus) == true)
	{
		vy = -0.28f;
		animate_rate = BIRD_BOOST_ANIMATE_RATE;
		if (pos_x < manager->samus->GetPosX())
		{
			vx = 0.05f;
		}
		else
		{
			vx = -0.05f;
		}
	}

	/*for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				SlideFromGround(manager->quadtreeGroup->objects[i], t, timeScale);

				DeathByShoot = false;
				if (pos_y - height <= GROUND_Y && normalx == 0)
				{
					if (this->DeathByShoot == false)
					{
						manager->birdbullets->Next(ON_LEFT, this->pos_x, pos_y);
						isActive = false;
					}
				}
			}
			break;
		}
	}*/


	// collider mới cho ground
	if (!(manager->metroid->isOnFloor))
	{
		for (int i = 0; i < manager->colGroundBrick->size; i++)
		{
			float timeScale = SweptAABB(manager->colGroundBrick->objects[i], t);
			if (timeScale < 1.0f)
			{
				ColliderBrick * brick = (ColliderBrick*)manager->colGroundBrick->objects[i];
				SlideFromGround(brick, t, timeScale);

				DeathByShoot = false;
				if (pos_y - height <= GROUND_Y && normalx == 0)
				{
					if (this->DeathByShoot == false)
					{
						manager->birdbullets->Next(ON_LEFT, this->pos_x, pos_y);
						isActive = false;
					}
				}
			}
		}
	}

	if (isHit)
	{
		isHit = false;
		return;
	}

	/*float scaletime = SweptAABB(manager->samus, t);
	if (scaletime < 1.0f)
	{
		Deflect(manager->samus, t, scaletime);
	}*/

	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / animate_rate)
	{
		fly->Next();
		last_time = now;
	}

	// --TO DO: Xử lý va chạm
	// ...
	// Khi cần xử lý va chạm, gọi groupCollision ở world
	//	
}

void Bird::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	fly->Render(pos_x, pos_y);
	spriteHandler->End();
}

bool Bird::IsCollide(GameObject * target)
{
	if (target->GetCollider() == NULL || this->collider_area == NULL)
		return false;
	if (pos_x + collider_area->GetRight() < target->GetPosX())
		return false;
	// Kiểm tra phía trên
	if (pos_y + collider_area->GetBottom() > target->GetPosY())
		return false;
	// Kiểm tra bên phải
	if (pos_x > target->GetPosX() + target->GetCollider()->GetRight())
		return false;
	// Kiểm tra phía dưới
	if (pos_y < target->GetPosY() - target->GetCollider()->GetBottom())
		return false;
	return true;
}

void Bird::Response(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{

}

void Bird::Destroy()
{
	// Effect explosion

	// Destroy
	vx = 0;

	manager->explsEffect->Init(this->pos_x, this->pos_y);	 // Xảy ra lỗi khi giết những mục tiêu to (Ridley, Mother Brain)
	// Drop item after destroyed
	int random;

	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	random = rand() % 10 + 1;

	if (random == 1 || random == 5)
		manager->energyItem->Init(this->pos_x, this->pos_y);
	else if (random == 7 || random == 9)
		manager->missileItem->Init(this->pos_x, this->pos_y);
	Enemy::Destroy();
}