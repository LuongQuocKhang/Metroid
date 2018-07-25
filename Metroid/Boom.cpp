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
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		boom->Render(pos_x, pos_y - 24);
		_SpriteHandler->End();
	}
}

Boom::Boom(World * manager)
{
	boom = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;

	this->time_survive = BOOM_TIME_SURVIVE;
	this->bulletType = BOOM;
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
	this->time_survive = ITEM_TIME_SURVIVE;
	damage = DAMAGE_SAMUS_BOOM;
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
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	boom = new Sprite(_SpriteHandler, BOOM_SPRITE_PATH, BOOM_SPRITE, BOOM_WIDTH, BOOM_HEIGHT, BOOM_COUNT, SPRITE_PER_ROW);
	time_survive = BOOM_TIME_SURVIVE;
		
}

void Boom::Update(float t)
{
	if (!isActive)
		return;
	// Xử lý va chạm
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
	}

	if ((manager->metroid->isOnFloor))
	{
		for (int i = 0; i < manager->colFloorBrick->size; i++)
		{
			float timeScale = SweptAABB(manager->colFloorBrick->objects[i], t);
			if (timeScale < 1.0f)
				Reset();
		}
	}
*/
	time_survive -= t;
	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		manager->explsEffect->Init(this->pos_x, this->pos_y - 20);
		collider->SetCollider(BOOM_HEIGHT * 3, -BOOM_WIDTH * 3, -BOOM_HEIGHT * 3, BOOM_WIDTH * 3);
		for (int i = 0; i < manager->enemyGroup->size; i++)
		{
			if (manager->enemyGroup->objects[i]->IsActive())
			{		
				//float timescale = SweptAABB(manager->enemyGroup->objects[i], t);
				//if (timescale < 1.0f || (timescale == 1 && ((Enemy*)manager->enemyGroup->objects[i])->GetEnemyType() == BIRD))
				//{
				//	manager->enemyGroup->objects[i]->isHit = true;
				//	((Enemy*)manager->enemyGroup->objects[i])->SetActive(false);
				//}
				if (IsCollide(manager->enemyGroup->objects[i]))
				{
					manager->enemyGroup->objects[i]->isHit = true;
					((Enemy*)manager->enemyGroup->objects[i])->SetActive(false);
				}
			}
		}
		isActive = false;
	}
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / 10)
	{
		boom->Next();
		last_time = now;
	}
}
