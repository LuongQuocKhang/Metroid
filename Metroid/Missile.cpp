#include "Missile.h"


void Missile::Render()
{
	if (isActive)
	{
		_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		switch (direction)
		{
		case ON_UP:
			missile_up->Render(pos_x, pos_y);
			break;
		case ON_LEFT:
			missile_left->Render(pos_x, pos_y + 10);
			break;
		case ON_RIGHT:
			missile_right->Render(pos_x, pos_y + 10);
			break;
		}
		_SpriteHandler->End();
	}
}

Missile::Missile(World * manager)
{
	missile_up = NULL;
	missile_left = NULL;
	missile_right = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;
	this->bulletType = MISSILE;
	damage = DAMAGE_SAMUS_MISSILE;

	//Set collider
	collider = new Collider(0, 0, -MISSILE_HEIGHT, MISSILE_WIDTH);
}

Missile::Missile(World * manager, int x_holder, int y_holder)
{
	missile_up = NULL;
	missile_left = NULL;
	missile_right = NULL;
	limit_dist_x = 0;
	limit_dist_y = 0;
	isActive = false;
	this->manager = manager;
	this->bulletType = MISSILE;
	damage = DAMAGE_SAMUS_MISSILE;

	pos_x_holder = x_holder;
	pos_y_holder = y_holder;
}


Missile::~Missile()
{
	delete(missile_up);
	delete(missile_left);
	delete(missile_right);
}

void Missile::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (result != D3D_OK) return;

	//Create sprite
	missile_up = new Sprite(_SpriteHandler, MISSILE_SPRITE_PATH, MISSILE_UP_SPRITE, MISSILE_UP_WIDTH, MISSILE_UP_HEIGHT, MISSILE_COUNT, SPRITE_PER_ROW);
	missile_left = new Sprite(_SpriteHandler, MISSILE_SPRITE_PATH, MISSILE_LEFT_SPRITE, MISSILE_WIDTH, MISSILE_HEIGHT, MISSILE_COUNT, SPRITE_PER_ROW);
	missile_right = new Sprite(_SpriteHandler, MISSILE_SPRITE_PATH, MISSILE_RIGHT_SPRITE, MISSILE_WIDTH, MISSILE_HEIGHT, MISSILE_COUNT, SPRITE_PER_ROW);
}
