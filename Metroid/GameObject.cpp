#include "GameObject.h"
#include <limits>
#include "Camera.h"
#include "Enemy.h"

GameObject::GameObject()
{
}

OBJECT_TYPE GameObject::GetType()
{
	return type;
}

void GameObject::SetType(OBJECT_TYPE type)
{
	this->type = type;
}

int GameObject::GetHealth()
{
	return health;
}

void GameObject::SetHealth(int value)
{
	health = value;
}

void GameObject::InitSprites()
{
}

GameObject::~GameObject()
{
	delete(sprite);
	delete(collider);
	delete(broadPhaseBox);
}

void GameObject::Render()
{
}

//void GameObject::Reset(int x, int y)
//{
//	isActive = true;
//	this->pos_x = x;
//	this->pos_y = y;
//}

void GameObject::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
}

void GameObject::Destroy()
{
}

void GameObject::Update(float t)
{
}

void GameObject::SetVelocityX(float value)
{
	vx = value;
}

float GameObject::GetVelocityX()
{
	return vx;
}

void GameObject::SetVelocityY(float value)
{
	vy = value;
}

float GameObject::GetVelocityY()
{
	return vy;
}

void GameObject::SetPosX(int value)
{
	pos_x = value;
}

float GameObject::GetPosX()
{
	return pos_x;
}

void GameObject::SetPosY(int value)
{
	pos_y = value;
}

float GameObject::GetPosY()
{
	return pos_y;
}

bool GameObject::IsActive()
{
	return isActive;
}

void GameObject::SetActive(bool value)
{
	this->isActive = value;
}

void GameObject::SetlastPosX(float posx)
{
	this->lastPosX = posx;
}
void GameObject::SetlastPosY(float posy)
{
	this->lastPosY = posy;
}

float GameObject::GetlastPosX()
{
	return this->lastPosX;
}
float GameObject::GetlastPosY()
{
	return lastPosY;
}

float GameObject::getgravity()
{
	return gravity;
}

void GameObject::setgravity(float value)
{
	gravity = value;
}

void GameObject::SetVelocityYLast(float value)
{
	this->vy_last = value;
}
float GameObject::GetVelocityYLast()
{
	return this->vy_last;
}

void GameObject::SetVelocityXLast(float value)
{
	vx_last = value;
}

float GameObject::GetVelocityXLast()
{
	return vx_last;
}

void GameObject::SetWidth(float value)
{
	width = value;
}

float GameObject::GetWidth()
{
	return width;
}

void GameObject::SetHeight(float value)
{
	height = value;
}

float GameObject::GetHeight()
{
	return height;
}

void GameObject::setNormalx(float value)
{
	this->normalx = value;
}

float GameObject::getNormalx()
{
	return this->normalx;
}

void GameObject::setNormaly(float value)
{
	this->normaly = value;
}

float GameObject::getNormaly()
{
	return this->normaly;
}

Collider * GameObject::GetCollider()
{
	return collider;
}

bool GameObject::IsInCamera()
{
	if (collider == NULL)
		return false;
	// Kiềm tra bên trái
	if (pos_x + collider->GetRight() < Camera::currentCamX)
		return false;
	// Kiểm tra phía trên
	if (pos_y + collider->GetBottom() > Camera::currentCamY)
		return false;
	// Kiểm tra bên phải
	if (pos_x > Camera::currentCamX + Camera::width)
		return false;
	// Kiểm tra phía dưới
	if (pos_y < Camera::currentCamY - Camera::height)
		return false;
	return true;
}

// Có va chạm hay lồng vào nhau hay ko ? ( xét va chạm )
bool GameObject::IsCollide(GameObject* target)
{
	// cả 2 phải có collider mới va chạm được
	if ((target->GetCollider() == NULL) || (this->collider == NULL))
		return false;

	//// cạnh trái của this > cạnh phải của target
	//if ((pos_x + collider->GetLeft()) > (target->GetPosX() + target->GetCollider()->GetRight()))
	//	return false;

	//// cạnh phải của this < cạnh trái của target
	//if ((pos_x + collider->GetRight()) < (target->GetPosX() + target->GetCollider()->GetLeft()))
	//	return false;

	//// cạnh trên của this < cạnh dưới của target
	//if ((pos_y + collider->GetTop()) < (target->GetPosY() + target->GetCollider()->GetBottom()))
	//	return false;

	//// cạnh dưới của this > cạnh trên của target
	//if ((pos_y + collider->GetBottom()) > (target->GetPosX() + target->GetCollider()->GetTop()))
	//	return false;

	//// ko thoả điều kiện nào hết => đang nằm lồng vào nhau
	//return true;


	// Kiềm tra bên trái
	if (pos_x + collider->GetRight() < target->GetPosX())
		return false;
	// Kiểm tra phía trên
	if (pos_y + collider->GetBottom() > target->GetPosY())
		return false;
	// Kiểm tra bên phải
	if (pos_x > target->GetPosX() + target->GetCollider()->GetRight())
		return false;
	// Kiểm tra phía dưới
	if (pos_y < target->GetPosY() - target->GetCollider()->GetBottom())
		return false;
	return true;
}
//////// khang
// kiểm tra xem có nằm bên trong (đang xuyên qua) hay ko ? (Xét va chạm)
bool GameObject::IsInside(GameObject* target)
{
	// cả 2 phải có collider mới va chạm được
	if ((target->GetCollider() == NULL) || (this->collider == NULL))
		return false;

	if (((pos_x + collider->GetLeft()) > (target->GetPosX() + target->GetCollider()->GetLeft())) &&
		((pos_x + collider->GetRight()) < (target->GetPosX() + target->GetCollider()->GetRight())) &&
		((pos_x + collider->GetTop()) < (target->GetPosX() + target->GetCollider()->GetTop())) &&
		((pos_x + collider->GetBottom()) > (target->GetPosX() + target->GetCollider()->GetBottom())))
		return true;

	// else
	return false;
}
// tính thời gian va chạm
float GameObject::SweptAABB(GameObject *target, const float &DeltaTime)
{
	if ((target->GetCollider() == NULL) || (this->collider == NULL))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	// ---------------======== Broad - Phasing ============-------------

	// delta velocity
	float deltaVX = ((this->vx) - (target->vx)) * DeltaTime;
	float deltaVY = ((this->vy) - (target->vy)) * DeltaTime;

	// tạo ra cái hộp bao quanh quỹ đạo của "this"
	if (broadPhaseBox == NULL)
	{
		broadPhaseBox = new Collider();
	}
	if (deltaVX > 0.0f)	// left & right
	{
		broadPhaseBox->SetLeft(this->collider->GetLeft());
		broadPhaseBox->SetRight(this->collider->GetRight() + deltaVX);
	}
	else
	{
		broadPhaseBox->SetLeft(this->collider->GetLeft() + deltaVX);
		broadPhaseBox->SetRight(this->collider->GetRight());
	}

	if (deltaVY > 0.0f) // top & bottom
	{
		broadPhaseBox->SetTop((this->collider->GetTop() + deltaVY));
		broadPhaseBox->SetBottom(this->collider->GetBottom());
	}
	else
	{
		broadPhaseBox->SetTop(this->collider->GetTop());
		broadPhaseBox->SetBottom((this->collider->GetBottom() + deltaVY));
	}

	// --- xét coi Box có lồng vào target hay không ------------------

	// cạnh trái của hộp > cạnh phải của target
	if ((pos_x + broadPhaseBox->GetLeft()) > (target->GetPosX() + target->GetCollider()->GetRight()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh phải của hộp < cạnh trái của target
	if ((pos_x + broadPhaseBox->GetRight()) < (target->GetPosX() + target->GetCollider()->GetLeft()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh trên của hộp < cạnh dưới của target
	if ((pos_y + broadPhaseBox->GetTop()) < (target->GetPosY() + target->GetCollider()->GetBottom()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh dưới của hộp > cạnh trên của target
	if ((pos_y + broadPhaseBox->GetBottom()) > (target->GetPosY() + target->GetCollider()->GetTop()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// end of Broad - Phasing
	// --------------------------===============================----------------------------


	// ---=== xét xem có lồng nhau ngay từ đầu không ===---
	if (this->IsCollide(target))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 0.0f;
	}

	float dxEntry, dyEntry;
	float dxExit, dyExit;

	if (deltaVX > 0.0f)
	{
		dxEntry = (target->GetPosX() + target->GetCollider()->GetLeft()) - (this->pos_x + this->collider->GetRight());
		dxExit = (target->GetPosX() + target->GetCollider()->GetRight()) - (this->pos_x + this->collider->GetLeft());
	}
	else
	{
		dxEntry = (target->GetPosX() + target->GetCollider()->GetRight()) - (this->pos_x + this->collider->GetLeft());
		dxExit = (target->GetPosX() + target->GetCollider()->GetLeft()) - (this->pos_x + this->collider->GetRight());
	}

	if (deltaVY > 0.0f)
	{
		dyEntry = (target->GetPosY() + target->collider->GetBottom()) - (this->pos_y + this->collider->GetTop());
		dyExit = (target->GetPosY() + target->collider->GetTop()) - (this->pos_y + this->collider->GetBottom());
	}
	else
	{
		dyEntry = (target->GetPosY() + target->collider->GetTop()) - (this->pos_y + this->collider->GetBottom());
		dyExit = (target->GetPosY() + target->collider->GetBottom()) - (this->pos_y + this->collider->GetTop());
	}

	// thời gian va chạm của mỗi chiều
	float txEntry, tyEntry;
	float txExit, tyExit;

	if (deltaVX == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / deltaVX;
		txExit = dxExit / deltaVX;
	}

	if (deltaVY == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / deltaVY;
		tyExit = dyExit / deltaVY;
	}

	// --- thời gian va chạn theo 2 chiều
	float entryTimeScale = max(txEntry, tyEntry);
	float exitTimeScale = min(txExit, tyExit);

	// nếu như không có va chạm
	if ((entryTimeScale > exitTimeScale) || ((txEntry < 0.0f) && (tyEntry < 0.0f))
		|| (txEntry > 1.0f) || (tyEntry > 1.0f))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}


	// tính toán vector pháp tuyến của bề mặt va chạm
	if (txEntry > tyEntry)
	{
		if (dxEntry < 0.0f)
		{
			normalx = 1.0f;
			normaly = 0.0f;
		}
		else
		{
			normalx = -1.0f;
			normaly = 0.0f;
		}
	}
	else
	{
		if (dyEntry < 0.0f)
		{
			normalx = 0.0f;
			normaly = 1.0f;
		}
		else
		{
			normalx = 0.0f;
			normaly = -1.0f;
		}
	}

	//	0.0f < scale < 1.0f là có va chạm
	// 0.0f va chạm lồng vào nhau
	return entryTimeScale;
}
////////////////////// khang
// di chuyển sát tường (xử lý va chạm)
void GameObject::Response(GameObject *target, const float &DeltaTime)
{
}
// bật ngược ra khi va chạm (Xử lý va chạm)
void GameObject::Deflect(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	// di chuyển vào sát tường trước
	//this->Response(target, DeltaTime, CollisionTimeScale);
	float distance = 0.0f;
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

	if (normaly != 0 )
	{
		pos_x += vx * (CollisionTimeScale)* DeltaTime;
		pos_y += vy * (CollisionTimeScale)* DeltaTime;
	}
}

// Phản xạ khi va chạm với ground
void GameObject::SlideFromGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale)
{
	//ResponseFrom(target, _DeltaTime, collisionTimeScale);
	// lỡ đụng 2,3 ground mà chạy cái này nhiều lần sẽ rất sai
	// "góc lag" sẽ làm đi luôn vào trong tường


	if (normalx > 0.1f)	// tông bên phải gạch
	{
		this->pos_x = (target->GetPosX() + target->collider->GetRight() - this->collider->GetLeft()) + 0.1f;
		pos_x -= vx*DeltaTime;
		//vx = 0.0f;
	}

	else if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->GetPosX() + target->collider->GetLeft() - this->collider->GetRight()) - 0.1f;
		pos_x -= vx*DeltaTime;
		//vx = 0.0f;
	}

	if (normaly > 0.1f) // trên xuống (không vào normaly được)
	{
		this->pos_y = (target->pos_y + target->collider->GetTop() - this->collider->GetBottom()) + 0.1f;
		pos_y -= vy*DeltaTime;
		vy = 0;
	}
	else if (normaly < -0.1f)	// tông ở dưới lên
	{
		//this->pos_y = (target->pos_y + target->collider->GetTop() - this->collider->GetBottom()) - 0.1f;
		pos_y -= vy*DeltaTime;
		vy = 0;
	}
	return;
}//----------------------------------