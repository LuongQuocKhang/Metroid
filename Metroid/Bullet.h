#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "BulletObject.h"
#include "Sprite.h"
#include "Parameters.h"

#define BULLET_SPRITE_PATH L"sprites\\bullet\\bullet.png"
#define BULLET_SPRITE "sprites\\bullet\\BULLET.txt"
#define BULLET_WIDTH 12
#define BULLET_HEIGHT 14
#define BULLET_COUNT 1
#define SPRITE_PER_ROW 1

#define SPEED 0.6f
#define LIMIT_DISTANCE 150



class Bullet : public BulletObject
{
protected:
	Sprite * bullet;
	
public:

	Bullet(World * manager);
	Bullet(World * manager, int x_holder, int y_holder);
	~Bullet();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void Update(float t);
	void Render();
};

#endif // !_BULLET_H
