#include "Energy.h"
#include "World.h"
#include "GroupObject.h"
#include "Samus.h"
#include "Camera.h"

int tempenergy, tempmissile;
Energy::Energy()
{
}

Energy::Energy(LPD3DXSPRITE spriteHandler, World * manager, TYPE type)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->type = type;
	this->isActive = true;

	//Khởi tạo sprites
	this->InitSprites();

	collider = new Collider();
}


Energy::~Energy()
{
	delete(energy);
}

void Energy::InitSprites()
{
	switch (type)
	{
	case ENERGYINFO:
		energy = new Sprite(spriteHandler, ENERGY_SPRITE_PATH, ENERGY_PATH, ENERGY_WIDTH, ENERGY_HEIGHT, ENERGY_SPRITE_COUNT, 1);
		break;
	case MISSILEINFO:
		energy = new Sprite(spriteHandler, MISSILE_INFO_SPRITE_PATH, MISSILE_PATH, MISSILE_INFO_WIDTH, MISSILE_INFO_HEIGHT, MISSILE_SPRITE_COUNT, 1);
		break;
	}
}

void Energy::Update(int t)
{
	switch (type)
	{
	case ENERGYINFO:
	{
		this->pos_x = Camera::currentCamX + 50;
		this->pos_y = Camera::currentCamY - 70;
	}
	break;
	case MISSILEINFO:
	{
		this->pos_x = Camera::currentCamX + 50;
		this->pos_y = Camera::currentCamY - 90;
	}
	break;
	}
}
void Energy::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	switch (type)
	{
	case ENERGYINFO:
	{
		energy->Render(pos_x, pos_y);
	}
	break;
	case MISSILEINFO:
	{
		energy->Render(pos_x, pos_y);
	}
	break;
	}

	spriteHandler->End();
}