#include "ColliderBrick.h"
#include "Metroid.h"
#include "World.h"

ColliderBrick::ColliderBrick()
{
}

ColliderBrick::ColliderBrick(LPD3DXSPRITE spriteHandler, World * manager, float posX, float posY, float width, float height)
{
	this->d3ddv = manager->metroid->GetDevice();
	this->type = COLLIDER_BRICK;
	this->pos_x = posX;
	this->pos_y = posY;
	this->width = width;
	this->height = height;

	isPassable = false;
	collider = new Collider(0, 0, -height, width);

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back_buffer);

	// Create a small off-screen surface (will fill it contain in GameRun)
	int result =
		d3ddv->CreateOffscreenPlainSurface(
			100,					// width 				
			100,					// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
			&surface,
			NULL);
}


ColliderBrick::~ColliderBrick()
{
}

void ColliderBrick::Render()
{
	
}
