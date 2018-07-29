#include "Boom.h"
#include "World.h"
#include "GroupObject.h"
#include "Metroid.h"
#include "Enemy.h"

void Boom::Render()
{
	if (!isActive)
		return;
	else
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		boom->Render(pos_x, pos_y);
		spriteHandler->End();
	}
}

Boom::Boom(LPD3DXSPRITE spriteHandler,World * manager)
{
	boom = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->damage = DAMAGE_SAMUS_BOOM;
	this->time_survive = BOOM_TIME_SURVIVE;
	this->bulletType = BOOM;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	collider = new Collider(BOOM_HEIGHT, -BOOM_WIDTH, -BOOM_HEIGHT, BOOM_WIDTH);
}

Boom::Boom(World * manager, int x_holder, int y_holder)
{
	boom = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;
	this->time_survive = BOOM_TIME_SURVIVE;;
	this->damage = DAMAGE_SAMUS_BOOM;
	this->bulletType = BOOM;
	pos_x_holder = x_holder;
	pos_y_holder = y_holder;
	//collider = new Collider(0, 0, -BOOM_HEIGHT, BOOM_WIDTH);
	collider = new Collider(BOOM_HEIGHT, -BOOM_WIDTH, -BOOM_HEIGHT, BOOM_WIDTH);
}


Boom::~Boom()
{
	delete(boom);
}

void Boom::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	boom = new Sprite(spriteHandler, BOOM_SPRITE_PATH, BOOM_SPRITE, BOOM_WIDTH, BOOM_HEIGHT, BOOM_COUNT, SPRITE_PER_ROW);
	time_survive = BOOM_TIME_SURVIVE;
		
}
void Boom::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 image)
{
	boom = new Sprite(spriteHandler, BOOM_SPRITE_PATH, BOOM_SPRITE, BOOM_WIDTH, BOOM_HEIGHT, BOOM_COUNT, SPRITE_PER_ROW);
}
void Boom::Update(float t)
{
	if (!isActive)
		return;
	// Xử lý va chạm
	if (!(manager->metroid->isOnFloor))
	{
		for (int i = 0; i < manager->colGroundBrick->size; i++)
		{
			float timeScale = SweptAABB(manager->colGroundBrick->objects[i], t);
			if (timeScale < 1.0f)
			{
				SlideFromGround(manager->colGroundBrick->objects[i], t, timeScale);
				Reset();
			}
		}
	}

	if ((manager->metroid->isOnFloor))
	{
		for (int i = 0; i < manager->colFloorBrick->size; i++)
		{
			float timeScale = SweptAABB(manager->colFloorBrick->objects[i], t);
			if (timeScale < 1.0f)
			{
				SlideFromGround(manager->colGroundBrick->objects[i], t, timeScale);
				Reset();
			}			
		}
	}

	time_survive -= t;
	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		manager->explsEffect->Init(this->pos_x, this->pos_y);
		collider->SetCollider(BOOM_HEIGHT * 3, -BOOM_WIDTH * 3, -BOOM_HEIGHT * 3, BOOM_WIDTH * 3);
		for (int i = 0; i < manager->enemyGroup->size; i++)
		{
			if (manager->enemyGroup->objects[i]->IsActive())
			{		
				if (IsCollide(manager->enemyGroup->objects[i]))
				{
					manager->enemyGroup->objects[i]->isHit = true;
					((Enemy*)manager->enemyGroup->objects[i])->TakeDamage(this->damage);
					Reset();
				}
			}
		}
		/*if (!(manager->metroid->isOnFloor))
		{
			for (int i = 0; i < manager->colGroundBrick->size; i++)
			{				
				float timeScale = SweptAABB(manager->colGroundBrick->objects[i], t);
				if (timeScale < 1.0f)
				{
					Reset();
				}
			}
		}*/
		isActive = false;
	}
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / 10)
	{
		boom->Next();
		last_time = now;
	}
}
