#pragma once
#ifndef _BOOM_H_
#define _BOOM_H_

#include "BulletObject.h"
#include "Sprite.h"
#include "Parameters.h"

#define BOOM_SPRITE_PATH L"sprites\\boom\\BOOM.png"
#define BOOM_SPRITE "sprites\\boom\\BOOM.txt"
#define BOOM_WIDTH 20
#define BOOM_HEIGHT 20
#define BOOM_COUNT 2
#define SPRITE_PER_ROW 1
class Boom : public BulletObject
{
protected:
	Sprite * boom;
	float time_survive;
public:

	Boom(World * manager);
	Boom(World * manager, int x_holder, int y_holder);
	Boom(LPD3DXSPRITE spriteHandler, World * manager);
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 image);
	~Boom();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Update(float t);
	void Render();
};

#endif // !_BOOM_H