#pragma once
#include "GameObject.h"
class ColliderBrick : public GameObject
{
private:
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 back_buffer;
	LPDIRECT3DSURFACE9 surface;
public:
	bool isPassable;
	ColliderBrick();
	ColliderBrick(LPD3DXSPRITE spriteHandler, World * manager, float posX, float posY, float width, float height);
	~ColliderBrick();
	void Render();
};

