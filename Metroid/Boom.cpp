#include "Boom.h"
#include "World.h"
#include "GroupObject.h"
#include "Metroid.h"

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
	collider = new Collider(BOOM_HEIGHT / 2, -BOOM_WIDTH / 2, -BOOM_HEIGHT / 2, BOOM_WIDTH / 2);
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
	time_survive = ITEM_TIME_SURVIVE;

}

void Boom::Update(float t)
{
	if (!isActive)
		return;

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
					case BOOM:hog_yellow->TakeDamage(this->damage); break;
					}
				}
				break;
				case BEDGEHOG_PINK:
				{

					Bedgehog * hog_pink = (Bedgehog*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{

					case BOOM:	hog_pink->TakeDamage(this->damage); break;
					}
				}

				break;
				case BIRD:
				{
					Bird * bird = (Bird*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{

					case BOOM:	bird->TakeDamage(this->damage); break;
					}
				}
				break;
				case BEE:
				{
					Bee * bee = (Bee*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{

					case BOOM:	bee->TakeDamage(this->damage); break;

					}
				}
				break;
				case RIDLEY:
				{
					Ridley * ridley = (Ridley*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{

					case BOOM:	ridley->TakeDamage(this->damage); break;
					}
				}
				break;
				case MOTHER_BRAIN:
				{
					MotherBrain * motherBrain = (MotherBrain*)manager->enemyGroup->objects[i];
					switch (getBulletType())
					{

					case BOOM:	motherBrain->TakeDamage(this->damage); break;
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
	if (!(manager->metroid->isOnFloor))
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

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		boom->Next();
		last_time = now;
	}

	// Tính thời gian hiển thị
	time_survive -= t;
	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		manager->explsEffect->Init(this->pos_x, this->pos_y - 20);
		isActive = false;
		Reset();

	}



}
