#include "Zoomer.h"

Zoomer::Zoomer()
{
	zoomer_up = NULL;
	zoomer_left = NULL;
	zoomer_right = NULL;
	zoomer_bottom = NULL;

	width = 32;
	height = 32;

	collider = new Collider();
	collider->SetCollider(0, 0, -height, width);
}

Zoomer::Zoomer(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	width = 32;
	height = 32;

	collider = new Collider();
	collider->SetCollider(0, 0, -height, width);
}


Zoomer::~Zoomer()
{
	delete(zoomer_up);
	delete(zoomer_left);
	delete(zoomer_right);
	delete(zoomer_bottom);

	delete(collider);
}

void Zoomer::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	zoomer_up = new Sprite(spriteHandler, ENEMY_SHEET_PATH, ZOOMER_UP, ZOOMER_UP_WIDTH, ZOOMER_UP_HEIGHT, ZOOMER_COUNT, SPRITE_PER_ROW);
	zoomer_left = new Sprite(spriteHandler, ENEMY_SHEET_PATH, ZOOMER_LEFT, ZOOMER_LEFT_WIDTH, ZOOMER_LEFT_HEIGHT, ZOOMER_COUNT, SPRITE_PER_ROW);
	zoomer_right = new Sprite(spriteHandler, ENEMY_SHEET_PATH, ZOOMER_RIGHT, ZOOMER_RIGHT_WIDTH, ZOOMER_RIGHT_HEIGHT, ZOOMER_COUNT, SPRITE_PER_ROW);
	zoomer_bottom = new Sprite(spriteHandler, ENEMY_SHEET_PATH, ZOOMER_BOTTOM, ZOOMER_BOTTOM_WIDTH, ZOOMER_BOTTOM_HEIGHT, ZOOMER_COUNT, SPRITE_PER_ROW);
}

void Zoomer::InitPostition()
{
	Enemy::InitPostition();

	pos_x = 70;
	pos_y = 100;
}

void Zoomer::InitPostition(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void Zoomer::Render()
{
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	zoomer_up->Render(pos_x, pos_y);
	spriteHandler->End();
}

void Zoomer::Update(int t)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		zoomer_up->Next();
		last_time = now;
	}
	//pos_x += vx*t;
	//pos_y += vy*t;
	Render();
}

void Zoomer::HandleCollision()
{
}
