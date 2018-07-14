#include "Samus.h"
#include "Game.h"
#include <vector>
#include "GroupObject.h"
#include "World.h"
#include "trace.h"
#include "ExplosionEffect.h"
#include "Metroid.h"
#include "Brick.h"
#include "PositionManager.h"
#include "ColliderBrick.h"
#include "EnergyItem.h"
#include "MissileItem.h"
#include "MorphItem.h"

void Samus::Render()
{	
	// Nếu không active thì không render
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	switch (state)
	{
	case APPEARANCE:
		appearing->Render(pos_x, pos_y);
		break;
	case RIGHTING:
		running_right->Render(pos_x, pos_y);
		break;
	case LEFTING:
		running_left->Render(pos_x, pos_y);
		break;
	case AIMING_UP_LEFT:
		run_aim_up_left->Render(pos_x, pos_y);
		break;
	case AIMING_UP_RIGHT:
		run_aim_up_right->Render(pos_x, pos_y);
		break;
	case IDLING_AIM_UP_LEFT:
		idle_aim_up_left->Render(pos_x, pos_y);
		break;
	case IDLING_AIM_UP_RIGHT:
		idle_aim_up_right-> Render(pos_x, pos_y);
		break;
	case IDLE_LEFT:
		idle_left->Render(pos_x, pos_y);
		break;
	case IDLE_RIGHT:
		idle_right->Render(pos_x, pos_y);
		break;
	case ON_MORPH_LEFT:
		morph_ball_left->Render(pos_x, pos_y);
		break;
	case ON_MORPH_RIGHT:
		morph_ball_right->Render(pos_x, pos_y);
		break;
	case ON_RUN_SHOOTING_LEFT:
		run_shooting_left->Render(pos_x, pos_y);
		break;
	case ON_RUN_SHOOTING_RIGHT:
		run_shooting_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_LEFT:
		jump_left->Render(pos_x, pos_y);
		break;
	case ON_JUMP_RIGHT:
		jump_right->Render(pos_x, pos_y);
		break;
	case ON_SOMERSAULT_LEFT:
		somersault_left->Render(pos_x, pos_y);
		break;
	case ON_SOMERSAULT_RIGHT:
		somersault_right->Render(pos_x, pos_y);
		break;
	case ON_JUMPING_SHOOTING_LEFT:
		jumping_shooting_left->Render(pos_x, pos_y);
		break;
	case ON_JUMPING_SHOOTING_RIGHT:
		jumping_shooting_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_AIM_UP_LEFT:
		jump_aim_up_left->Render(pos_x, pos_y);
		break;
	case ON_JUMP_AIM_UP_RIGHT:
		jump_aim_up_right->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_LEFT:
		idle_shooting_left->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_RIGHT:
		idle_shooting_right->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_UP_LEFT:
		idle_shooting_up_left->Render(pos_x, pos_y);
		break;
	case IDLING_SHOOTING_UP_RIGHT:
		idle_shooting_up_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_SHOOTING_UP_LEFT:
		jump_shooting_up_right->Render(pos_x, pos_y);
		break;
	case ON_JUMP_SHOOTING_UP_RIGHT:
		jump_shooting_up_right->Render(pos_x, pos_y);
		break;
	}
	
	spriteHandler->End();
}

void Samus::Destroy()
{
	//Ngưng active
	isActive = false;
	Game::gameSound->stopSound(BACKGROUND_MAP);
	Game::gameSound->playSound(BACKGROUND_SAMUS_DEATH);
	manager->explsEffect->Init(pos_x, pos_y);
	
	isDeath = true;
	//--TO DO: Đưa Samus ra khỏi viewport

}

void Samus::TakeDamage(float damage)
{
	health -= damage;
	Game::gameSound->playSound(SAMUS_HIT_ENEMY);

	//int randomX = rand() % 32 - 16;
	//int randomY = rand() % 32 - 16;
	//Effect* newEffect = Effect::CreateEffect(EFFECT_HIT, this->postX + randomX, this->postY + randomY, 1, spriteHandler, manager);
	//manager->groupEffect->AddObject(newEffect);

	if (health <= 0)
		Destroy();
}

void Samus::_Shoot(BULLET_DIRECTION dir, Metroid * metroid)
{
	metroid->SetNow_shoot(GetTickCount());
	if (metroid->GetStart_shoot() <= 0) //if shooting is active
	{
		metroid->SetStart_shoot(GetTickCount());
		(metroid->GetWorld())->bullets->Next(dir, this->GetPosX(), this->GetPosY());
	}
	else if ((metroid->GetNow_shoot() - metroid->GetStart_shoot()) > SHOOTING_SPEED * metroid->GetTickPerFrame())
	{
		//Reset start_shoot
		metroid->SetStart_shoot(0);
	}
}

void Samus::_ShootMissile(BULLET_DIRECTION dir, Metroid * metroid)
{
	(metroid->GetWorld())->missiles->Next(dir, this->GetPosX(), this->GetPosY());
}

void Samus::SetHealth(float value)
{
	health = value;
}

float Samus::GetHealth()
{
	return health;
}

Samus::Samus()
{
	appearing = NULL;
	running_left = NULL;
	running_right = NULL;
	jump_left = NULL;
	jump_right = NULL;

	width = 40;
	height = 64;

	collider = new Collider();
	collider->SetCollider(0, 0, -this->height, this->width);
	this->isActive = true;
	state = APPEARANCE;
}

Samus::Samus(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->isActive = true;
	this->isDeath = false;
	this->isMorph = false;
	//Set type
	this->type = SAMUS;

	// Khởi tạo máu cho Samus
	health = HEALTH_SAMUS;

	width = 40;
	height = 50;

	//Collider
	this->collider = new Collider();
	this->collider->SetCollider(0, 0, -this->height, this->width - 10);
	state = APPEARANCE;
	gravity = FALLDOWN_VELOCITY_DECREASE;
}


Samus::~Samus()
{
	delete(appearing);
	delete(running_left);
	delete(running_right);
	delete(jump_left);
	delete(jump_right);
	delete(run_shooting_left);
	delete(run_shooting_right);
	delete(run_aim_up_left);
	delete(run_aim_up_right);
	delete(idle_aim_up_left);
	delete(idle_aim_up_right);
	delete(idle_left);
	delete(idle_right);
	delete(morph_ball_left);
	delete(morph_ball_right);
	delete(somersault_left);
	delete(somersault_right);
	delete(jumping_shooting_left);
	delete(jumping_shooting_right);
	delete(jump_aim_up_left);
	delete(jump_aim_up_right);
	delete(collider);
	delete(idle_shooting_left);
	delete(idle_shooting_right);
	delete(idle_shooting_up_left);
	delete(idle_shooting_up_right);
	delete(jump_shooting_up_left);
	delete(jump_shooting_up_right);
}

//DirectCollision Samus::getDirection()
//{
//	return this->direction;
//}
//void Samus::setDirection(DirectCollision direction)
//{
//	this->direction = direction;
//}


void Samus::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;

	//Create instance of sprites
	appearing = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, APPEARING, APPEARING_WIDTH, APPEARING_HEIGHT, APPEARING_COUNT, SPRITE_PER_ROW);
	running_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUNNING_LEFT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	running_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUNNING_RIGHT, RUNNING_WIDTH, RUNNING_HEIGHT, RUNNING_COUNT, SPRITE_PER_ROW);
	jump_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_LEFT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	jump_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_RIGHT, JUMP_WIDTH, JUMP_HEIGHT, JUMP_COUNT, SPRITE_PER_ROW);
	run_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_LEFT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);
	run_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_SHOOTING_RIGHT, RUN_SHOOTING_WIDTH, RUN_SHOOTING_HEIGHT, RUN_SHOOTING_COUNT, SPRITE_PER_ROW);
	run_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_LEFT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	run_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, RUN_AIM_UP_RIGHT, RUN_AIM_UP_WIDTH, RUN_AIM_UP_HEIGHT, RUN_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_LEFT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, IDLE_AIM_UP_RIGHT, IDLE_AIM_UP_WIDTH, IDLE_AIM_UP_HEIGHT, IDLE_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STANDING_LEFT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	idle_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STANDING_RIGHT, STANDING_WIDTH, STANDING_HEIGHT, STANDING_COUNT, SPRITE_PER_ROW);
	morph_ball_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, MORPH_BALL_LEFT, MORPH_BALL_WIDTH, MORPH_BALL_HEIGHT, MORPH_BALL_COUNT, SPRITE_PER_ROW);
	morph_ball_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, MORPH_BALL_RIGHT, MORPH_BALL_WIDTH, MORPH_BALL_HEIGHT, MORPH_BALL_COUNT, SPRITE_PER_ROW);
	somersault_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, SOMERSAULT_LEFT, SOMERSAULT_WIDTH, SOMERSAULT_HEIGHT, SOMERSAULT_COUNT, SPRITE_PER_ROW);
	somersault_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, SOMERSAULT_RIGHT, SOMERSAULT_WIDTH, SOMERSAULT_HEIGHT, SOMERSAULT_COUNT, SPRITE_PER_ROW);
	jumping_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMPING_SHOOTING_LEFT, JUMPING_SHOOTING_WIDTH, JUMPING_SHOOTING_HEIGHT, JUMPING_SHOOTING_COUNT, SPRITE_PER_ROW);
	jumping_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMPING_SHOOTING_RIGHT, JUMPING_SHOOTING_WIDTH, JUMPING_SHOOTING_HEIGHT, JUMPING_SHOOTING_COUNT, SPRITE_PER_ROW);
	jump_aim_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_AIM_UP_LEFT, JUMP_AIM_UP_WIDTH, JUMP_AIM_UP_HEIGHT, JUMP_AIM_UP_COUNT, SPRITE_PER_ROW);
	jump_aim_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_AIM_UP_RIGHT, JUMP_AIM_UP_WIDTH, JUMP_AIM_UP_HEIGHT, JUMP_AIM_UP_COUNT, SPRITE_PER_ROW);
	idle_shooting_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_LEFT, STANDING_SHOOTING_WIDTH, STANDING_SHOOTING_HEIGHT, STAND_SHOOTING_COUNT, SPRITE_PER_ROW);
	idle_shooting_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_RIGHT, STANDING_SHOOTING_WIDTH, STANDING_SHOOTING_HEIGHT, STAND_SHOOTING_COUNT, SPRITE_PER_ROW);
	idle_shooting_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_UP_LEFT, STANDING_SHOOTING_UP_WIDTH, STANDING_SHOOTING_UP_HEIGHT, STAND_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
	idle_shooting_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, STAND_SHOOTING_UP_RIGHT, STANDING_SHOOTING_UP_WIDTH, STANDING_SHOOTING_UP_HEIGHT, STAND_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
	jump_shooting_up_left = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_SHOOTING_UP_LEFT, JUMP_SHOOTING_UP_WIDTH, JUMP_SHOOTING_UP_HEIGHT, JUMP_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
	jump_shooting_up_right = new Sprite(spriteHandler, SAMUS_SPRITES_PATH, JUMP_SHOOTING_UP_RIGHT, JUMP_SHOOTING_UP_WIDTH, JUMP_SHOOTING_UP_HEIGHT, JUMP_SHOOTING_UP_COUNT, SPRITE_PER_ROW);
}

void Samus::InitPostition()
{
	//--TO DO: This code will be edited soon
	pos_x = 50;
	pos_y = GROUND_Y;

	vx = 0;
	vx_last = 1.0f;
	vy = 0;

	//Init state of samus
	state = APPEARANCE;
}

int max_camera_x = 300;
int max_camera_y = 480;

int min_camera_x = 0;
int min_camera_y = 480;


SAMUS_STATE Samus::GetState()
{
	return state;
}

void Samus::SetState(SAMUS_STATE value)
{
	state = value;
}

void Samus::ResetAllSprites()
{
	appearing->Reset();
	running_left->Reset();
	running_right->Reset();
	jump_left->Reset();
	jump_right->Reset();
	run_shooting_left->Reset();
	run_shooting_right->Reset();
	run_aim_up_left->Reset();
	run_aim_up_right->Reset();
	idle_aim_up_left->Reset();
	idle_aim_up_right->Reset();
	idle_left->Reset();
	idle_right->Reset();
	morph_ball_left->Reset();
	morph_ball_right->Reset();
	somersault_left->Reset();
	somersault_right->Reset();
	jumping_shooting_left->Reset();
	jumping_shooting_right->Reset();
	jump_aim_up_left->Reset();
	jump_aim_up_right->Reset();
	idle_shooting_left->Reset();
	idle_shooting_right->Reset();
	idle_shooting_up_left->Reset();
	idle_shooting_up_right->Reset();
	jump_shooting_up_left->Reset();
	jump_shooting_up_right->Reset();
}

bool Samus::isSamusDeath()
{
	if (isDeath == true)
		return true;
}

bool Samus::isSamusCrouch()
{
	if (isMorph == true)
		return true;
}

bool Samus::isSamusOnAir()
{
	if (isOnAir == true)
		return true;
	return false;
}

bool Samus::GetStateActive()
{
	return isActive;
}


void Samus::Reset(int x, int y)
{
	// Cho samus active trở lại
	isActive = true;

	//Đặt lại vị trí
	this->pos_x = x;
	this->pos_y = y;
	isMorph = false;
	isDeath = false;
	manager->morphItem->Init(706, 196);
	Camera::currentCamX = 1000 - 240;
	Camera::currentCamY = 480;
	health = HEALTH_SAMUS;
}

void Samus::Update(float t)
{
	//
	// Update samus status
	//
	//GameObject::Update(t);

	vy -= gravity;
	
	for (int i = 0; i < manager->enemyGroup->size; i++)
	{	
		Enemy * enemy = (Enemy*)manager->enemyGroup->objects[i];
		if (enemy->IsActive())
		{
			float timeScale = SweptAABB(enemy, t);
			if (timeScale < 1.0f)
			{
				//Xử lý khi va chạm với enemy
				Deflect(enemy, t, timeScale);
				// xong rồi tùy con mà takedamage
				TakeDamage(enemy->damage);				
			}
		}
	}
	//<======================

	// Xử lý va chạm với Item
	if (SweptAABB(manager->energyItem, t) < 1.0f)
	{
		if (manager->energyItem->IsActive() == true)
		{
			Game::gameSound->playSound(SAMUS_HIT_LIFE_POINT);
			this->health += manager->energyItem->getNumberGain();
			manager->energyItem->Destroy();
		}
	}

	if (SweptAABB(manager->missileItem, t) < 1.0f)
	{
		if (manager->missileItem->IsActive() == true)
		{
			Game::gameSound->playSound(SAMUS_HIT_LIFE_POINT);
			//manager->missiles->setNum(manager->missile.getNum() +manager->missileItem->getNumberGain(); Chưa dùng được
			manager->missileItem->Destroy();
		}

	}
	if (SweptAABB(manager->morphItem, t) < 1.0f)
	{
		if (manager->morphItem->IsActive() == true)
		{
			isMorph = true;
			Game::gameSound->stopSound(BACKGROUND_MAP);
			Game::gameSound->playSound(BACKGROUND_ITEM_ACQUIRED);
			manager->morphItem->Destroy();

			manager->metroid->isFreezing = true;
		}
	}
	//----------------------------
	
	//Xử lý va chạm với ground
	for (int i = 0; i < manager->quadtreeGroup->size; i++)
	{
		switch (manager->quadtreeGroup->objects[i]->GetType())
		{
		case BRICK:
			Brick * brick = (Brick*)(manager->quadtreeGroup->objects[i]);
			float timeScale = SweptAABB(manager->quadtreeGroup->objects[i], t);
			if (timeScale < 1.0f)
			{
				if (brick->IsPassable())
				{
					if (this->vx > 0)
					{
						Camera::moveRight = true;
						
						if (manager->posManager->GetIndexRoom() <= 1)
							manager->posManager->Next();	// tăng index pooling đến room kế tiếp
						else if (manager->posManager->GetIndexRoom() == 2)
						{
							manager->posManager->Next();
							manager->metroid->isOnFloor = true;
						}
						else if (manager->posManager->GetIndexRoom() == 4)
							manager->posManager->Back();

						this->pos_x += 65;
					}
					else if (this->vx < 0)
					{
						Camera::moveLeft = true;

						if (manager->posManager->GetIndexRoom() < 3)
							manager->posManager->Back();	// giảm index pooling đến room phía sau
						else if (manager->posManager->GetIndexRoom() == 3)
							manager->posManager->Next();	// vào room boss
						
						this->pos_x -= 65;
					}
				}
				else
					SlideFromGround(manager->quadtreeGroup->objects[i], t, timeScale);
				//Response(manager->quadtreeGroup->objects[i], t, timeScale);
			}
			break;
		}
	}

	//Xử lý va chạm với colBrick khi đang ở floor
	if (manager->metroid->isOnFloor)
	{
		for (int i = 0; i < manager->colBrick->size; i++)
		{
			float timeScale = SweptAABB(manager->colBrick->objects[i], t);
			if (timeScale < 1.0f)
			{
				ColliderBrick * brick = (ColliderBrick*)manager->colBrick->objects[i];
				if (brick->isPassable == true)
				{
					if (this->vx > 0)
					{
						Camera::moveRight = true;

						if (manager->posManager->GetIndexRoom() <= 1)
							manager->posManager->Next();	// tăng index pooling đến room kế tiếp
						else if (manager->posManager->GetIndexRoom() == 2)
						{
							manager->posManager->Next();
							manager->metroid->isOnFloor = true;
						}
						else if (manager->posManager->GetIndexRoom() == 4)	// ra khỏi phòng boss
						{
							manager->posManager->Back();

							//Tắt nhạc phòng boss và bật nhạc nền ở đây
							Game::gameSound->stopSound(BACKGROUND_MOTHER_BRAIN_BOSS);
							Game::gameSound->playSoundLoop(BACKGROUND_MAP);
						}

						this->pos_x += 65;
					}
					else if (this->vx < 0)
					{
						Camera::moveLeft = true;

						if (manager->posManager->GetIndexRoom() < 3)
							manager->posManager->Back();	// giảm index pooling đến room phía sau
						else if (manager->posManager->GetIndexRoom() == 3)
						{
							manager->posManager->Next();	// vào room boss
							
							//tắt nhạc nền và thêm nhạc phòng boss ở đây
							Game::gameSound->playSoundLoop(BACKGROUND_MOTHER_BRAIN_BOSS);
							Game::gameSound->stopSound(BACKGROUND_MAP);
						}

						this->pos_x -= 65;

					}
				}
				else
					SlideFromGround(brick, t, timeScale);
			}
		}
	}

	//Xử lý va chạm với static object
	for (int i = 0; i < manager->otherGO->size; i++)
	{
		float timeScale = SweptAABB(manager->otherGO->objects[i], t);
		if (timeScale < 1.0f)
		{
			switch (manager->otherGO->objects[i]->GetType())
			{
			case SENTRY:
			case GATE:
			{
				this->SlideFromGround(manager->otherGO->objects[i], t, timeScale);
				break;
			}
			}
		}
	}


	//float collisiontime = SweptAABB(manager->gateleft, t);
	//	if (collisiontime < 1.0f)
	//	{
	//		if (manager->gateleft->IsActive())
	//		{
	//			this->SlideFromGround(manager->gateleft, t, collisiontime);
	//		}
	//	}

	//	float collisiontime1 = SweptAABB(manager->gateright, t);
	//	if (collisiontime1 < 1.0f)
	//	{
	//		if (manager->gateright->IsActive())
	//		{
	//			this->SlideFromGround(manager->gateright, t, collisiontime1);
	//		}
	//	}
	
	pos_x += vx*t;
	pos_y += vy*t;

	Camera::SetCameraX(pos_x, t);
	Camera::SetCameraY(pos_y, t);

	// Animate samus if he is running
	//trace((LPWSTR)t);
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case APPEARANCE:
			appearing->Next();
			break;
		case RIGHTING:
			running_right->Next();
			break;
		case LEFTING:
			running_left->Next();
			break;
		case AIMING_UP_LEFT:
			run_aim_up_left->Next();
			break;
		case AIMING_UP_RIGHT:
			run_aim_up_right->Next();
			break;
		case IDLING_AIM_UP_LEFT:
			idle_aim_up_left->Next();
			break;
		case IDLING_AIM_UP_RIGHT:
			idle_aim_up_right->Next();
			break;
		case ON_MORPH_LEFT:
			morph_ball_left->Next();
			break;
		case ON_MORPH_RIGHT:
			morph_ball_right->Next();
			break;
		case ON_RUN_SHOOTING_LEFT:
			run_shooting_left->Next();
			break;
		case ON_RUN_SHOOTING_RIGHT:
			run_shooting_right->Next();
			break;
		case ON_JUMP_LEFT:
			jump_left->Next();
			break;
		case ON_JUMP_RIGHT:
			jump_right->Next();
			break;
		case ON_SOMERSAULT_LEFT:
			somersault_left->Next();
			break;
		case ON_SOMERSAULT_RIGHT:
			somersault_right->Next();
			break;
		case ON_JUMPING_SHOOTING_LEFT:
			jumping_shooting_left->Next();	
			break;
		case ON_JUMPING_SHOOTING_RIGHT:
			jumping_shooting_right->Next();
			break;
		case ON_JUMP_AIM_UP_LEFT:
			jump_aim_up_left->Next();
			break;
		case ON_JUMP_AIM_UP_RIGHT:
			jump_aim_up_right->Next();
			break;
		case IDLING_SHOOTING_LEFT:
			idle_shooting_left->Next();
			break;
		case IDLING_SHOOTING_RIGHT:
			idle_shooting_right->Next();
			break;
		case IDLING_SHOOTING_UP_LEFT:
			idle_shooting_up_left->Next();
			break;
		case IDLING_SHOOTING_UP_RIGHT:
			idle_shooting_up_right->Next();
			break;
		case ON_JUMP_SHOOTING_UP_LEFT:
			jump_shooting_up_left->Next();
			break;
		case ON_JUMP_SHOOTING_UP_RIGHT:
			jump_shooting_up_right->Next();
			break;

		}
		last_time = now;
	}	

	//Check if samus is on ground or not
	/*if (pos_y > GROUND_Y)
	{
		vy -= gravity;
	}
	else
	{
		pos_y = GROUND_Y;
		vy = 0;
		if (state == ON_JUMP_LEFT || state == ON_JUMPING_SHOOTING_LEFT || state == ON_SOMERSAULT_LEFT || state == ON_JUMP_AIM_UP_LEFT)
		{
			state = IDLE_LEFT;
		}
		else if (state == ON_JUMP_RIGHT || state == ON_JUMPING_SHOOTING_RIGHT || state == ON_SOMERSAULT_RIGHT || state == ON_JUMP_AIM_UP_RIGHT)
		{
			state = IDLE_RIGHT;
		}
	}*/

	//Render
	//Render();

}

void Samus::Response(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	
	// rồi mới bật ra
	if (normalx > 0.1f)	// tông bên phải
	{
		if (vx < -0.0f)// đang chạy qua trái => văng ngược lại
			vx *= -1;
	}
	else if (normalx < -0.1f) // tông bên trái
	{
		if (vx > 0.0f)//	đang chạy qua phải => văng ngược lại
			vx *= -1;
	}

	if (normaly > 0.1f) // tông phía trên
	{
		if (vy < -0.0f)// đang rơi xuống => văng lên trên
			vy = 0.0f;
		if (state == ON_JUMP_LEFT || state == ON_JUMPING_SHOOTING_LEFT || state == ON_SOMERSAULT_LEFT || state == ON_JUMP_AIM_UP_LEFT)
		{
			state = IDLE_LEFT;
		}
		else if (state == ON_JUMP_RIGHT || state == ON_JUMPING_SHOOTING_RIGHT || state == ON_SOMERSAULT_RIGHT || state == ON_JUMP_AIM_UP_RIGHT)
		{
			state = IDLE_RIGHT;
		}
	}
	else if (normaly < -0.1f) // tông phía dưới
	{
		if (vy > 0.0f)// đang bay lên => văng xuống
			vy *= -1;
	}

	pos_x += vx * (CollisionTimeScale)* DeltaTime;
	pos_y += vy * (CollisionTimeScale)* DeltaTime;
}

// Phản xạ khi va chạm với ground
void Samus::SlideFromGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	//ResponseFrom(target, _DeltaTime, collisionTimeScale);
	// lỡ đụng 2,3 ground mà chạy cái này nhiều lần sẽ rất sai
	// "góc lag" sẽ làm đi luôn vào trong tường

	//this->Slide(target, 1.0f - CollisionTimeScale);

	if (normalx > 0.1f)	// tông bên phải gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetRight() - this->collider->GetLeft()) + 0.1f;
		pos_x -= vx*DeltaTime;
		//vx = 0.0f;
	}

	else if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetLeft() - this->collider->GetRight()) - 0.1f;
		pos_x -= vx*DeltaTime;
		//vx = 0.0f;
	}

	if (normaly > 0.1f) // trên xuống (không vào normaly được)
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
		//pos_y -= vy*DeltaTime;
		vy = 0;

		// Xử lý trạng thái cho samus
		if (state == ON_JUMP_LEFT || state == ON_JUMPING_SHOOTING_LEFT || state == ON_SOMERSAULT_LEFT || state == ON_JUMP_AIM_UP_LEFT)
		{
			state = IDLE_LEFT;
		}
		else if (state == ON_JUMP_RIGHT || state == ON_JUMPING_SHOOTING_RIGHT || state == ON_SOMERSAULT_RIGHT || state == ON_JUMP_AIM_UP_RIGHT)
		{
			state = IDLE_RIGHT;
		}

	}
	else if (normaly < -0.1f)	// tông ở dưới lên
	{
		//this->pos_y = (target->pos_y + target->collider->GetTop() - this->collider->GetBottom()) - 0.1f;
		pos_y -= vy*DeltaTime;
		vy = 0;
	}
	return;
}
void Samus::Deflect(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	// di chuyển vào sát tường trước
	//this->Response(target, DeltaTime, CollisionTimeScale);

	// rồi mới bật ra
	if (normalx > 0.1f)	// tông bên phải
	{
		if (vx < -0.0f)// đang chạy qua trái => văng ngược lại
			vx *= -1;
	}
	else if (normalx < -0.1f) // tông bên trái
	{
		if (vx > 0.0f)//	đang chạy qua phải => văng ngược lại
			vx *= -1;
	}

	if (normaly > 0.1f) // tông phía trên
	{
		if (vy < -0.0f)// đang rơi xuống => văng lên trên
			vy = 0.0f;
	}
	else if (normaly < -0.1f) // tông phía dưới
	{
		if (vy > 0.0f)// đang bay lên => văng xuống
			vy *= -1;
	}

	if (normaly != 0)
	{
		pos_x += vx * (CollisionTimeScale)* DeltaTime + 15.0f*normalx;
		pos_y += vy * (CollisionTimeScale)* DeltaTime + 15.0f*normaly;
	}
}
void Samus::Slide(GameObject *target, float remainingtime)
{
	float dotprod = (this->GetVelocityX() * normaly + this->GetVelocityY() * normalx) * remainingtime;
	this->SetVelocityX(dotprod * normalx);
	this->SetVelocityY(dotprod * normaly);
}

void Samus::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta,Metroid* metroid)
{
	if (metroid->isInGame)
		return;

	if (metroid->IsKeyDown(DIK_RIGHT))
	{

		/*Camera::currentCamX += 2.0f;
		float c = Camera::currentCamY + 5;*/

		//this->setNormalx(1.0f);
		//this->setgravity(FALLDOWN_VELOCITY_DECREASE);
		this->SetVelocityXLast(this->GetVelocityX());
		this->SetVelocityX(SAMUS_SPEED);
		if (this->GetState() != ON_MORPH_LEFT && this->GetState() != ON_MORPH_RIGHT
			&& this->GetState() != ON_JUMP_LEFT && this->GetState() != ON_JUMP_RIGHT
			&& this->GetState() != ON_JUMPING_SHOOTING_LEFT && this->GetState() != ON_JUMPING_SHOOTING_RIGHT
			&& this->GetState() != ON_SOMERSAULT_LEFT && this->GetState() != ON_SOMERSAULT_RIGHT)
		{
			this->SetState(RIGHTING);
		}
	}
	else if (metroid->IsKeyDown(DIK_LEFT))
	{
		//Camera::currentCamX -= 2.0f;

		//this->setgravity(FALLDOWN_VELOCITY_DECREASE);
		//this->setNormalx(-1.0f);
		this->SetVelocityXLast(this->GetVelocityX());
		this->SetVelocityX(-SAMUS_SPEED);
		if (this->GetState() != ON_MORPH_LEFT && this->GetState() != ON_MORPH_RIGHT
			&& this->GetState() != ON_JUMP_LEFT && this->GetState() != ON_JUMP_RIGHT
			&& this->GetState() != ON_JUMPING_SHOOTING_LEFT && this->GetState() != ON_JUMPING_SHOOTING_RIGHT
			&& this->GetState() != ON_SOMERSAULT_LEFT && this->GetState() != ON_SOMERSAULT_RIGHT)
		{
			this->SetState(LEFTING);
		}
	}
	else
	{
		this->SetVelocityX(0);

		if (this->GetVelocityXLast() < 0)
		{
			if (this->GetState() != ON_MORPH_LEFT && this->GetState() != ON_JUMP_LEFT && this->GetState() != ON_JUMP_RIGHT
				&& this->GetState() != ON_JUMPING_SHOOTING_LEFT && this->GetState() != ON_JUMPING_SHOOTING_RIGHT
				&& this->GetState() != ON_SOMERSAULT_LEFT && this->GetState() != ON_SOMERSAULT_RIGHT
				&& this->GetState() != ON_JUMP_AIM_UP_LEFT && this->GetState() != APPEARANCE)
			{
				this->SetState(IDLE_LEFT);
				this->ResetAllSprites();
			}
		}
		else
		{
			if (this->GetState() != ON_MORPH_RIGHT && this->GetState() != ON_JUMP_LEFT && this->GetState() != ON_JUMP_RIGHT
				&& this->GetState() != ON_JUMPING_SHOOTING_LEFT && this->GetState() != ON_JUMPING_SHOOTING_RIGHT
				&& this->GetState() != ON_SOMERSAULT_LEFT && this->GetState() != ON_SOMERSAULT_RIGHT
				&& this->GetState() != ON_JUMP_AIM_UP_RIGHT && this->GetState() != APPEARANCE)
			{
				this->SetState(IDLE_RIGHT);
				this->ResetAllSprites();
			}
		}
	}

	if (metroid->IsKeyDown(DIK_UP))
	{
		if (this->GetState() == LEFTING)
			this->SetState(AIMING_UP_LEFT);
		if (this->GetState() == RIGHTING)
			this->SetState(AIMING_UP_RIGHT);
		if (this->GetState() == IDLE_LEFT)
			this->SetState(IDLING_AIM_UP_LEFT);
		if (this->GetState() == IDLE_RIGHT)
			this->SetState(IDLING_AIM_UP_RIGHT);
		if (this->GetState() == ON_JUMP_LEFT/* || this->GetState() == ON_JUMPING_SHOOTING_LEFT*/)
		{
			this->SetState(ON_JUMP_AIM_UP_LEFT);
			Game::gameSound->playSound(JUMP);
		}
		if (this->GetState() == ON_JUMP_RIGHT/* || this->GetState() == ON_JUMPING_SHOOTING_RIGHT*/)
		{
			this->SetState(ON_JUMP_AIM_UP_RIGHT);
			Game::gameSound->playSound(JUMP);
		}
		if (this->GetState() == ON_MORPH_LEFT)
			this->SetState(IDLE_LEFT);
		if (this->GetState() == ON_MORPH_RIGHT)
			this->SetState(IDLE_RIGHT);
	}

	if (metroid->IsKeyDown(DIK_Z))
	{
		//Để mặc định đạn thường trước
		Game::gameSound->playSound(SHOOT_BULLET);
		//State Đứng bắn lên
		if (this->GetState() == IDLING_AIM_UP_LEFT)
		{
			this->SetState(IDLING_SHOOTING_UP_LEFT);

			_Shoot(ON_UP,metroid);
		}
		if (this->GetState() == IDLING_AIM_UP_RIGHT)
		{
			this->SetState(IDLING_SHOOTING_UP_RIGHT);

			_Shoot(ON_UP,metroid);
		}
		//State Chạy bắn lên
		if (this->GetState() == AIMING_UP_LEFT)
		{
			this->SetState(AIMING_UP_LEFT);
			_Shoot(ON_UP,metroid);
		}
		if (this->GetState() == AIMING_UP_RIGHT)
		{
			this->SetState(AIMING_UP_RIGHT);
			_Shoot(ON_UP,metroid);
		}
		//State Nhảy bắn lên => bug
		if (this->GetState() == ON_JUMP_AIM_UP_LEFT)
		{
			this->SetState(ON_JUMP_SHOOTING_UP_LEFT);

			_Shoot(ON_UP,metroid);
		}
		if (this->GetState() == ON_JUMP_AIM_UP_RIGHT)
		{
			this->SetState(ON_JUMP_SHOOTING_UP_RIGHT);

			_Shoot(ON_UP,metroid);
		}
		//State nhảy bắn
		if (this->GetState() == ON_JUMP_LEFT || this->GetState() == ON_SOMERSAULT_LEFT || this->GetState() == ON_JUMPING_SHOOTING_LEFT)
		{
			this->SetState(ON_JUMPING_SHOOTING_LEFT);

			_Shoot(ON_LEFT,metroid);
		}
		if (this->GetState() == ON_JUMP_RIGHT || this->GetState() == ON_SOMERSAULT_RIGHT || this->GetState() == ON_JUMPING_SHOOTING_RIGHT)
		{
			this->SetState(ON_JUMPING_SHOOTING_RIGHT);

			_Shoot(ON_RIGHT,metroid);
		}
		//State chạy bắn
		if (this->GetState() == LEFTING)
		{
			this->SetState(ON_RUN_SHOOTING_LEFT);

			_Shoot(ON_LEFT,metroid);
		}
		if (this->GetState() == RIGHTING)
		{
			this->SetState(ON_RUN_SHOOTING_RIGHT);

			_Shoot(ON_RIGHT,metroid);
		}
		//State đứng bắn
		if (this->GetState() == IDLE_LEFT)
		{
			this->SetState(IDLING_SHOOTING_LEFT);

			_Shoot(ON_LEFT,metroid);
		}
		if (this->GetState() == IDLE_RIGHT)
		{
			this->SetState(IDLING_SHOOTING_RIGHT);

			_Shoot(ON_RIGHT,metroid);
		}

		BulletObject ** list = this->getlistbullet();
		int num = this->getNumBullet();
		for (int i = 0; i < (metroid->GetWorld())->enemyGroup->size; i++)
		{
			for (int j = 0; j < num; j++)
			{
				float TimeScale = (metroid->GetWorld())->enemyGroup->objects[i]->SweptAABB(list[j], Delta);
				if (TimeScale < 1.0f)
				{
					if ((metroid->GetWorld())->enemyGroup->objects[i]->IsActive())
					{
						float damge = DAMAGE_SAMUS_BULLET;
						((Enemy*)((metroid->GetWorld())->enemyGroup->objects[i]))->DeathByShoot = true;
						((Enemy*)((metroid->GetWorld())->enemyGroup->objects[i]))->TakeDamage(damge);
						//list[j]->Reset();
						break;
					}
				}

			}
		}
	}

	if (this->GetVelocityY() < 0)
	{
		//this->setNormaly(-1.0f);
	}
}

void Samus::OnkeyDown(int KeyCode, Metroid * metroid ,int& screenMode)
{
	this->isOnAir = false;

	if (this->isSamusOnAir() == false)
	{
		switch (KeyCode)
		{
		case DIK_X:
			if (metroid->IsKeyDown(DIK_X))
			{
				Game::gameSound->playSound(JUMP);
				this->isOnAir = true;
				this->setNormaly(1.0f);
				if (this->GetState() != ON_SOMERSAULT_RIGHT && metroid->IsKeyDown(DIK_RIGHT)/*&& samus->GetState() != ON_JUMP_AIM_UP_RIGHT*/)
				{
					metroid->SetStart_jump(GetTickCount());

					this->SetState(ON_SOMERSAULT_RIGHT);
					this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

					metroid->SetNow_jump(GetTickCount());
					if ((metroid->GetNow_jump() - metroid->GetStart_jump()) <= 10 * metroid->GetTickPerFrame())
					{
						this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST);
					}
				}

				if (this->GetState() != ON_SOMERSAULT_LEFT && metroid->IsKeyDown(DIK_LEFT)/*&& samus->GetState() != ON_JUMP_AIM_UP_LEFT*/)
				{
					metroid->SetStart_jump(GetTickCount());
					metroid->SetNow_jump(GetTickCount());
					this->SetState(ON_SOMERSAULT_LEFT);
					this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

					//now_jump = GetTickCount();
					if ((metroid->GetNow_jump() - metroid->GetStart_jump()) <= 10 * metroid->GetTickPerFrame())
					{
						this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST);
					}
				}

				if (this->GetVelocityXLast() < 0)
				{
					if (this->GetState() != ON_JUMP_LEFT && this->GetState() != ON_SOMERSAULT_LEFT
						&& this->GetState() != ON_JUMPING_SHOOTING_LEFT && this->GetState() != ON_JUMP_AIM_UP_LEFT)
					{
						metroid->SetStart_jump(GetTickCount());
						metroid->SetNow_jump(GetTickCount());
						if (this->GetState() == IDLING_AIM_UP_LEFT)
							this->SetState(ON_JUMP_AIM_UP_LEFT);
						else
							this->SetState(ON_JUMP_LEFT);
						this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

						/*now_jump = GetTickCount();*/
						if ((metroid->GetNow_jump() - metroid->GetStart_jump()) <= 10 * metroid->GetTickPerFrame())
						{
							this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST);
						}
					}
					//else
					//{
					//	now_jump = GetTickCount();
					//	if ((now_jump - start_jump) <= 10 * tick_per_frame)
					//	{
					//		this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST);
					//	}
					//}
				}
				if (this->GetVelocityXLast() > 0)
				{
					if (this->GetState() != ON_JUMP_RIGHT && this->GetState() != ON_SOMERSAULT_RIGHT
						&& this->GetState() != ON_JUMPING_SHOOTING_RIGHT && this->GetState() != ON_JUMP_AIM_UP_RIGHT)
					{
						metroid->SetStart_jump(GetTickCount());
						metroid->SetNow_jump(GetTickCount());
						if (this->GetState() == IDLING_AIM_UP_RIGHT)
							this->SetState(ON_JUMP_AIM_UP_RIGHT);
						else
							this->SetState(ON_JUMP_RIGHT);
						this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST_FIRST);

						//now_jump = GetTickCount();
						if ((metroid->GetNow_jump() - metroid->GetStart_jump()) <= 10 * metroid->GetTickPerFrame())
						{
							this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST);
						}
					}
					//else
					//{
					//	now_jump = GetTickCount();
					//	if ((now_jump - start_jump) <= 10 * tick_per_frame)
					//	{
					//		this->SetVelocityY(this->GetVelocityY() + JUMP_VELOCITY_BOOST);

					//	}
					//}
				}
			}
		}
	}

	switch (screenMode)
	{
		// intro
	case GAMEMODE_INTRO:
	{
		if (KeyCode == DIK_RETURN)
		{
			screenMode = GAMEMODE_START;
		}
		break;
	}
	// start screen
	case GAMEMODE_START://------------------------------------------------
	{
		if (KeyCode == DIK_RETURN)
		{
			screenMode = GAMEMODE_GAMERUN;
			Game::gameSound->stopSound(BACKGROUND_INTRO);
			Game::gameSound->playSound(BACKGROUND_APPEARANCE);
			metroid->isInGame = true;
		}
	}
	break;
	// game running
	case GAMEMODE_GAMERUN:// -------------------------------------------------
	{
		switch (KeyCode)
		{
		case DIK_DOWN:
			//if samus is idle then do morph
			if (this->isSamusCrouch() == true)
			{
				if (this->GetState() == IDLE_LEFT)
				{
					this->SetVelocityX(0);
					this->ResetAllSprites();
					this->SetState(ON_MORPH_LEFT);
					this->GetCollider()->SetCollider(0, 0, -MORPH_BALL_HEIGHT, MORPH_BALL_WIDTH);
				}
				else if (this->GetState() == IDLE_RIGHT)
				{
					this->SetVelocityX(0);
					this->ResetAllSprites();
					this->SetState(ON_MORPH_RIGHT);
					this->GetCollider()->SetCollider(0, 0, -MORPH_BALL_HEIGHT, MORPH_BALL_WIDTH);
				}
				else if (this->GetState() == ON_MORPH_LEFT) //otherwise, reset to idle (left of right)
				{
					this->SetVelocityX(0);
					this->ResetAllSprites();
					this->SetState(IDLE_LEFT);
					//this->setDirection(DirectCollision::RIGHT);
					this->SetPosY(this->GetPosY() + this->GetHeight() + MORPH_BALL_HEIGHT);
					this->GetCollider()->SetCollider(0, 0, -this->GetHeight(), 24);
				}
				else if (this->GetState() == ON_MORPH_RIGHT)
				{
					this->SetVelocityX(0);
					this->ResetAllSprites();
					this->SetState(IDLE_RIGHT);
					this->SetPosY(this->GetPosY() + this->GetHeight() + MORPH_BALL_HEIGHT);
					this->GetCollider()->SetCollider(0, 0, -this->GetHeight(), 24);
					//this->setDirection(DirectCollision::LEFT);
				}
				break;
			}
			//case DIK_X:
			//	//**********************************************************************************
			//	// [CAUTION!!!] Vi pos_y chua chinh theo toa do World, code duoi day chi la tam thoi,
			//	// se cap nhat lai sau
			//	if (samus->GetPosY() >= GROUND_Y)
			//	{
			//		if (samus->GetVelocityXLast() < 0)
			//		{
			//			samus->SetState(ON_JUMP_LEFT);
			//			samus->SetVelocityY(samus->GetVelocityY() - JUMP_VELOCITY_BOOST);
			//		}
			//		else if (samus->GetVelocityXLast() > 0)
			//		{
			//			samus->SetState(ON_JUMP_RIGHT);
			//			samus->SetVelocityY(samus->GetVelocityY() - JUMP_VELOCITY_BOOST);
			//		}
			//	}
			//	//***********************************************************************************
			//	break;
		case DIK_LEFT:
			/*if (samus->GetState() == ON_JUMP_RIGHT)
			samus->SetState(ON_JUMP_LEFT);*/
			if (this->GetState() == ON_MORPH_RIGHT)
				this->SetState(ON_MORPH_LEFT);
			/*else if (samus->GetState() != ON_MORPH_LEFT && samus->GetState() != ON_JUMP_LEFT && samus->GetState() != ON_JUMP_RIGHT
			&& samus->GetState() != ON_SOMERSAULT_RIGHT)
			samus->SetState(LEFTING);*/
			break;
		case DIK_RIGHT:
			/*if (samus->GetState() == ON_JUMP_LEFT)
			samus->SetState(ON_JUMP_RIGHT);*/
			if (this->GetState() == ON_MORPH_LEFT)
				this->SetState(ON_MORPH_RIGHT);
			/*else if (this->GetState() != ON_MORPH_RIGHT && this->GetState() != ON_JUMP_LEFT && this->GetState() != ON_JUMP_RIGHT
			&& this->GetState() != ON_SOMERSAULT_LEFT)
			this->SetState(RIGHTING);*/
			break;

		case DIK_C:
			Game::gameSound->playSound(SHOOT_MISSILE);
			if (this->GetState() == IDLING_AIM_UP_LEFT)
			{
				this->SetState(IDLING_SHOOTING_UP_LEFT);

				_ShootMissile(ON_UP,metroid);
			}
			if (this->GetState() == IDLING_AIM_UP_RIGHT)
			{
				this->SetState(IDLING_SHOOTING_UP_RIGHT);

				_ShootMissile(ON_UP,metroid);
			}
			//State Chạy bắn lên
			if (this->GetState() == AIMING_UP_LEFT)
			{
				this->SetState(AIMING_UP_LEFT);
				_ShootMissile(ON_UP,metroid);
			}
			if (this->GetState() == AIMING_UP_RIGHT)
			{
				this->SetState(AIMING_UP_RIGHT);
				_ShootMissile(ON_UP,metroid);
			}
			//State Nhảy bắn lên => bug
			if (this->GetState() == ON_JUMP_AIM_UP_LEFT)
			{
				this->SetState(ON_JUMP_SHOOTING_UP_LEFT);

				_ShootMissile(ON_UP,metroid);
			}
			if (this->GetState() == ON_JUMP_AIM_UP_RIGHT)
			{
				this->SetState(ON_JUMP_SHOOTING_UP_RIGHT);

				_ShootMissile(ON_UP,metroid);
			}
			//State nhảy bắn
			if (this->GetState() == ON_JUMP_LEFT || this->GetState() == ON_SOMERSAULT_LEFT || this->GetState() == ON_JUMPING_SHOOTING_LEFT)
			{
				this->SetState(ON_JUMPING_SHOOTING_LEFT);

				_ShootMissile(ON_LEFT,metroid);
			}
			if (this->GetState() == ON_JUMP_RIGHT || this->GetState() == ON_SOMERSAULT_RIGHT || this->GetState() == ON_JUMPING_SHOOTING_RIGHT)
			{
				this->SetState(ON_JUMPING_SHOOTING_RIGHT);

				_ShootMissile(ON_RIGHT,metroid);
			}
			//State chạy bắn
			if (this->GetState() == LEFTING)
			{
				this->SetState(ON_RUN_SHOOTING_LEFT);

				_ShootMissile(ON_LEFT,metroid);
			}
			if (this->GetState() == RIGHTING)
			{
				this->SetState(ON_RUN_SHOOTING_RIGHT);

				_ShootMissile(ON_RIGHT,metroid);
			}
			//State đứng bắn
			if (this->GetState() == IDLE_LEFT)
			{
				this->SetState(IDLING_SHOOTING_LEFT);

				_ShootMissile(ON_LEFT,metroid);
			}
			if (this->GetState() == IDLE_RIGHT)
			{
				this->SetState(IDLING_SHOOTING_RIGHT);

				_ShootMissile(ON_RIGHT,metroid);

			}
			break;

		}
	}
	// game over
	case GAMEMODE_GAMEOVER://------------------------------------------------
	{
		if (KeyCode == DIK_RETURN)
		{
			screenMode = GAMEMODE_INTRO;
			Game::gameSound->playSound(BACKGROUND_INTRO);
			this->Reset(1275, 150);
		}
		break;
	}
	}
}
//----------------------------------