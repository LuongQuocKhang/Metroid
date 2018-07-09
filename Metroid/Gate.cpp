#include "Gate.h"

Gate::Gate(LPD3DXSPRITE spriteHandler, World * manager, GATE_TYPE type)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->type = GATE;
	this->width = GATE_WIDTH;
	this->height = GATE_HEIGHT;

	char* exists_path = NULL;
	char* destroy_path = NULL;

	//Init sprites
	switch (type)
	{
	case GATE_TYPE::LEFT:
		exists_path = GATE_LEFT_EXISTS;
		destroy_path = GATE_LEFT_DESTROYING;
		gate_type = LEFT;
		break;
	case GATE_TYPE::RIGHT:
		exists_path = GATE_RIGHT_EXISTS;
		destroy_path = GATE_RIGHT_DESTROYING;
		gate_type = RIGHT;
		break;
	}

	exists = new Sprite(spriteHandler, GATE_SPRITES_PATH, exists_path, GATE_WIDTH, GATE_HEIGHT, GATE_EXISTS_COUNT, 1);
	destroying = new Sprite(spriteHandler, GATE_SPRITES_PATH, destroy_path, GATE_WIDTH, GATE_HEIGHT, GATE_DESTROYING_COUNT, 1);

	//Set state
	state = GATE_STATE::CLOSE;

	//Set time survive
	time_survive = GATE_TIME_SURVIVE;

	//Set collider
	collider = new Collider(0, 0, -GATE_HEIGHT, GATE_WIDTH);
}

Gate::~Gate()
{
	delete(exists);
	delete(destroying);
}

GATE_TYPE Gate::GetGateType()
{
	return gate_type;
}

void Gate::Update(float t)
{
	if (!isActive)
		return;

	if (!IsInCamera())
	{
		isActive = false;
		return;
	}

	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case DESTROYING:
			destroying->Next();
			if (destroying->GetIndex() == destroying->GetCount() - 1)
			{
				state = OPEN;
				isActive = false;
				collider = NULL;
			}
			break;
		}
		last_time = now;
	}
}

void Gate::Render()
{
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (state)
	{
	case CLOSE:
		exists->Render(pos_x, pos_y);
		break;
	case DESTROYING:
		destroying->Render(pos_x, pos_y);
		break;
	}
	spriteHandler->End();
}

void Gate::DestroyGate()
{
	//Đặt state là destroy để hủy cổng
	state = DESTROYING;
}
