#include "Bedgehog.h"
#include "World.h"
#include "GroupObject.h"
#include "ColliderBrick.h"
#include "Metroid.h"
#include "utils.h"


Bedgehog::Bedgehog()
{

}

Bedgehog::Bedgehog(LPD3DXSPRITE spriteHandler, World * manager, ENEMY_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->enemy_type = enemy_type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	//Set collider
	collider = new Collider();
	collider->SetCollider(0, 0, -BEDGEHOG_HEIGHT, BEDGEHOG_WIDTH);

	//Set vận tốc
	//gravity = FALLDOWN_VELOCITY_DECREASE;
	vx = BEDGEHOG_SPEED;
	vy = -BEDGEHOG_SPEED;

	last_normalx = 0;
	last_normaly = 0;

	//isCollision = false;
}


Bedgehog::~Bedgehog()
{
	delete(up);
	delete(bottom);
	delete(left);
	delete(right);
}


void Bedgehog::InitSprites()
{

	char *up_path = NULL, *bottom_path = NULL, *left_path = NULL, *right_path = NULL;

	switch (enemy_type)
	{
	case BEDGEHOG_YELLOW:
		up_path = BEDGEHOG_YELLOW_UP;
		bottom_path = BEDGEHOG_YELLOW_BOTTOM;
		left_path = BEDGEHOG_YELLOW_LEFT;
		right_path = BEDGEHOG_YELLOW_RIGHT;

		//Khởi tạo máu
		health = HEALTH_BEDGEHOG_YELLOW;

		//Khởi tạo sát thương
		damage = DAMAGE_BEDGEHOG;
		break;
	case BEDGEHOG_PINK:
		up_path = BEDGEHOG_PINK_UP;
		bottom_path = BEDGEHOG_PINK_BOTTOM;
		left_path = BEDGEHOG_PINK_LEFT;
		right_path = BEDGEHOG_PINK_RIGHT;

		//Khởi tạo máu
		health = HEALTH_BEDGEHOG_PINK;

		//Khởi tạo sát thương
		damage = DAMAGE_BEDGEHOG;
		break;
	}

	//// Khởi tạo sprite
	up = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, up_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);
	bottom = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, bottom_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);
	left = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, left_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);
	right = new Sprite(spriteHandler, ENEMY_SPRITE_PATH, right_path, BEDGEHOG_WIDTH, BEDGEHOG_HEIGHT, BEDGEHOG_SPRITE_COUNT, 1);

}

void Bedgehog::Update(float t)
{
	// isCollision = false;

	if (!isActive)
	{
		last_normalx = 0;
		last_normaly = 0;
		return;
	}


	// Nếu không nằm trong Camera thì unactive
	if (!IsInCamera())
	{
		isActive = false;
		last_normalx = 0;
		last_normaly = 0;
		return;
	}

	if (time_freeze <= 300)
		collider->SetCollider(0, 0, -BEDGEHOG_HEIGHT, BEDGEHOG_WIDTH);

	if (isHit)
	{
		time_freeze -= t;
		if (time_freeze <= 0)
		{
			isHit = false;
			time_freeze = ENEMY_FREEZE;
		}
		return;
	}

	bool isCollide = false;
	// collider mới cho ground - Quan
	if (!(manager->metroid->isOnFloor))
	{
		for (int i = 0; i < manager->colGroundBrick->size; i++)
		{
			float timeScale = SweptAABB(manager->colGroundBrick->objects[i], t);
			if (timeScale < 1.0f)
			{
				ColliderBrick * brick = (ColliderBrick*)manager->colGroundBrick->objects[i];
				ResponseGround3(brick, t, timeScale);

				isCollide = true;
				isChange = false;


				//break;
			}
		}
	}

	if (manager->metroid->isOnFloor)
	{
		for (int i = 0; i < manager->colFloorBrick->size; i++)
		{
			float timeScale = SweptAABB(manager->colFloorBrick->objects[i], t);
			// Nếu có va chạm
			if (timeScale < 1.0f)
			{
				ColliderBrick * brick = (ColliderBrick*)manager->colFloorBrick->objects[i];
				ResponseGround3(brick, t, timeScale);

				isCollide = true;
				isChange = false;
			}
		}
	}



	if (!isCollide && !isChange)
	{
		isChange = true;
		//OutputDebugString(L"NOT Collided\n");
		if ((last_normaly > 0.1f) || (last_normaly < -0.1f))// nếu frame trước va chạm dưới hoặc trên còn bây giờ thì ko
		{
			if (vx > 0)
			{
				pos_x += 2.f;
			}
			else
			{
				pos_x -= 2.f;
			}

			//OutputDebugString(L"pos_x: ");
			//Output(pos_x);
			//OutputDebugString(L"\n");

			vx *= -1;
			//vx = 0;
			if (vx > 0)
				OutputDebugString(L"vx > 0 \n");
			else
				OutputDebugString(L"vx < 0 \n");
			if (last_normaly > 0.1f)
			{
				OutputDebugString(L"Up --> Right\n");
			}
			else
			{
				OutputDebugString(L"Down --> Left\n");
			}
			last_normalx = 0;
			last_normaly = 0;
		}

		if ((last_normalx > 0.1f) || (last_normalx < -0.1f))// nếu frame trước va chạm trái hoặc phải còn bây giờ thì ko
		{
			if (vy > 0)
			{
				pos_y += 2.f;	// +
				OutputDebugString(L"vy > 0\n");
			}
			else
			{
				pos_y -= 2.f;
				OutputDebugString(L"vy < 0\n");
			}
			vy *= -1;
			if (last_normalx > 0.1f)
				OutputDebugString(L"Right --> Down\n");
			else
				OutputDebugString(L"Left --> Up\n");
			last_normaly = 0;
			last_normalx = 0;
		}

		/*last_normalx = normalx;
		last_normaly = normaly;*/
	}



	/*last_normalx = normalx;
	last_normaly = normaly;*/



	/*if (!isCollision && gravity == 0)
	{
	if (last_normalx > 0.1f)
	{
	state = ON_BEDGEHOG_BOTTOM;
	vx = -BEDGEHOG_SPEED;
	vy = 0.01f;
	}
	else if (last_normalx < -0.1f)
	{
	state = ON_BEDGEHOG_UP;
	vx = BEDGEHOG_SPEED;
	vy = -0.01f;
	}

	if (last_normaly > 0.1f)
	{
	state = ON_BEDGEHOG_RIGHT;
	vx = -0.01f;
	vy = -0.05f;
	}
	else if (last_normaly < -0.1f)
	{
	vx = 0.01f;
	vy = 0.05f;
	state = ON_BEDGEHOG_LEFT;
	}
	}*/


	pos_x += vx * t;
	pos_y += vy * t;

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case ON_BEDGEHOG_UP:
			up->Next();
			break;
		case ON_BEDGEHOG_BOTTOM:
			bottom->Next();
			break;
		case ON_BEDGEHOG_LEFT:
			left->Next();
			break;
		case ON_BEDGEHOG_RIGHT:
			right->Next();
			break;
		}
		last_time = now;
	}

}

void Bedgehog::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	if (time_freeze <= 300) // Do ENEMY_FREEZE = 300
	{
		switch (state)
		{
		case ON_BEDGEHOG_UP:
			up->Render(pos_x, pos_y);
			break;
		case ON_BEDGEHOG_BOTTOM:
			bottom->Render(pos_x, pos_y);
			break;
		case ON_BEDGEHOG_LEFT:
			left->Render(pos_x, pos_y);
			break;
		case ON_BEDGEHOG_RIGHT:
			right->Render(pos_x, pos_y);
			break;
		}
	}
	else
	{
		D3DXCOLOR color;
		color.r = 255; color.g = 255; color.b = 255;
		switch (state)
		{
		case ON_BEDGEHOG_UP:
			up->Render(pos_x, pos_y, color);
			break;
		case ON_BEDGEHOG_BOTTOM:
			bottom->Render(pos_x, pos_y, color);
			break;
		case ON_BEDGEHOG_LEFT:
			left->Render(pos_x, pos_y, color);
			break;
		case ON_BEDGEHOG_RIGHT:
			right->Render(pos_x, pos_y, color);
			break;
		}
	}

	spriteHandler->End();
}

void Bedgehog::Destroy()
{
	// Effect explosion
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

	// Destroy
	Enemy::Destroy();
}

// Phản xạ khi va chạm với ground
void Bedgehog::ResponseGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{

	if (normaly > 0.1f) // trên xuống ()
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
		pos_y -= vy * DeltaTime;

		gravity = 0;
		vx = BEDGEHOG_SPEED;
		vy = -0.05f;

		state = ON_BEDGEHOG_UP;

		last_normaly = normaly;
		last_normalx = 0;
	}
	else if (normaly < -0.1f)	// tông ở dưới lên
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetBottom() - this->collider->GetTop()) - 0.1f;
		pos_y -= vy * DeltaTime;
		/*gravity = -FALLDOWN_VELOCITY_DECREASE + 0.02f;*/
		vx = -BEDGEHOG_SPEED;
		vy = 0.05f;

		state = ON_BEDGEHOG_BOTTOM;

		last_normaly = normaly;
		last_normalx = 0;
	}
	else if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetLeft() - this->collider->GetRight()) - 0.1f;
		pos_x -= vx * DeltaTime;
		//pos_y += 0.1f;
		//
		////Test 
		gravity = 0;
		vx = 0.001f;
		vy = 0.05f;

		state = ON_BEDGEHOG_LEFT;

		last_normalx = normalx;
		last_normaly = 0;
	}
	//else if (normalx > 0.1f)	// tông bên phải gạch
	//{
	//	this->pos_x = (target->GetPosX() + target->GetCollider()->GetRight() - this->collider->GetLeft()) + 0.1f;
	//	pos_x -= vx*DeltaTime;

	//	gravity = 0;
	//	vx = -0.001;
	//	vy = -0.05f;

	//	state = ON_BEDGEHOG_RIGHT;

	//	last_normalx = normalx;
	//}
	return;
}
void Bedgehog::ResponseGround2(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{
	if (normaly > 0.1f) // trên xuống ()
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
		pos_y -= vy * DeltaTime;

		gravity = 0;
		vx = BEDGEHOG_SPEED;
		vy = -0.05f;

		state = ON_BEDGEHOG_UP;

		last_normaly = normaly;
		last_normalx = 0;
	}
	else if (normaly < -0.1f)	// tông ở dưới lên
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetBottom() - this->collider->GetTop()) - 0.1f;
		pos_y -= vy * DeltaTime;
		/*gravity = -FALLDOWN_VELOCITY_DECREASE + 0.02f;*/
		vx = -BEDGEHOG_SPEED;
		vy = 0.05f;

		state = ON_BEDGEHOG_BOTTOM;

		last_normaly = normaly;
		last_normalx = 0;
	}
	else if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetLeft() - this->collider->GetRight()) - 0.1f;
		pos_x -= vx * DeltaTime;
		//pos_y += 0.1f;
		//
		////Test 
		gravity = 0;
		vx = 0.001f;
		vy = 0.05f;

		state = ON_BEDGEHOG_LEFT;

		last_normalx = normalx;
		last_normaly = 0;
	}
	//else if (normalx > 0.1f)	// tông bên phải gạch
	//{
	//	this->pos_x = (target->GetPosX() + target->GetCollider()->GetRight() - this->collider->GetLeft()) + 0.1f;
	//	pos_x -= vx*DeltaTime;

	//	gravity = 0;
	//	vx = -0.001;
	//	vy = -0.05f;

	//	state = ON_BEDGEHOG_RIGHT;

	//	last_normalx = normalx;
	//}
	return;
}
void Bedgehog::ResponseGround3(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{
	if (normalx > 0.1f)	// tông bên phải gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetRight() - this->collider->GetLeft()) + 0.1f;
		pos_x -= vx * DeltaTime;
		last_normalx = normalx;
		//last_normaly = 0;

		state = ON_BEDGEHOG_RIGHT;
	}

	if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->GetPosX() + target->GetCollider()->GetLeft() - this->collider->GetRight()) - 0.1f;
		pos_x -= vx * DeltaTime;
		last_normalx = normalx;
		//last_normaly = 0;

		state = ON_BEDGEHOG_LEFT;
	}

	if (normaly > 0.1f) // trên xuống 
	{
		this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) + 0.1f;
		pos_y -= vy * DeltaTime;
		last_normaly = normaly;
		//last_normalx = 0;

		state = ON_BEDGEHOG_UP;
	}

	if (normaly < -0.1f)	// tông ở dưới lên
	{
		//this->pos_y = (target->GetPosY() + target->GetCollider()->GetTop() - this->collider->GetBottom()) - 0.1f;
		pos_y -= vy * DeltaTime;
		//vy = 0;
		last_normaly = normaly;
		//last_normalx = 0;

		state = ON_BEDGEHOG_BOTTOM;
	}


	if ((last_normaly > 0.1f && normaly == 0.0f) || (last_normaly < -0.1f && normaly == 0.0f))// nếu frame trước va chạm dưới còn bây giờ thì ko
	{
		vx *= -1;
	}
	if ((last_normalx > 0.1f && normalx == 0.0f) || (last_normalx < -0.1f && normalx == 0.0f))// nếu frame trước va chạm trái còn bây giờ thì ko
	{
		vy *= -1;
	}
}
//----------------------------------