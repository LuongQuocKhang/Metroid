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
	void RenderDebug(LPDIRECT3DDEVICE9 d3ddv, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 0));
};

